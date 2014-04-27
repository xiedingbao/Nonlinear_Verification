%{
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "hybridReach.h"
	#define DEBUG true

	bool syntax_error=false;
	extern int yylex();
	extern int inputbound;
  	extern unsigned int line_number;
	Automaton *aut;	

	void yyerror(const char *msg){	
		syntax_error=true;
     		printf("Parse error in line %d: ", line_number);
      		printf("%s\n", msg);
		exit(1);
	}
	void yyerror(const string s){
     		yyerror(s.c_str());
	}
	int check_var(string name){
		if(name=="t")
			yyerror("t is an internal variable, you can't use it as the name of variable");
		int id = aut->getIDForVar(name);
		if(id < 0){
			yyerror("Unknown identifier '" + name +"'.");;
		}
		return id;
	}
%}

%type<automaton> automaton 
%type<varlist> vars  var_list
%type<conlist> invariant_set guard_set constr_list
%type<resetlist> assign_set
%type<reset>  assign_set_no_and
%type<ODElist> ODES
%type<state> location
%type<poly>  ODEpolynomial polynomial
%type<ODE> ODEsolution
%type<polycon> constraint constr_list_no_and 
%type<transitionlist> transition_list
%type<transition> transition

%union{
	char * mystring;
	Automaton* automaton;
	vector<State>* locationlist;
	vector<string>* varlist;
	vector<Solution>* ODElist;
	vector<Transition>* transitionlist;
	vector<PolynomialConstraint>* conlist;
	vector<resetMap>* resetlist;
	resetMap* reset;
	Solution* ODE;	
	State* state;
	Transition* transition;	
	Polynomial* poly;
	PolynomialConstraint* polycon;
};

%token EVENTS
%token AUTOMATON
%token VAR
%token SYNCLABS
%token INITIALLY
%token LOC
%token WHILE
%token WAIT
%token WHEN
%token DO
%token SYNC
%token GOTO
%token END
%token ASSIGN
%token FORBIDDEN
%token TRUE
%token FALSE
%token <mystring> NUM IDENT 


//%nonassoc '(' ')'
%left  '&'
%left OGE OLE OGT OLT OEQ OEQ2
%left '+' '-'
%left '*' '/'
%left '!'
%left '(' ')'
%left PRIM
%nonassoc uminus
%right '^'

%%	

program:
	commands
	{
	}
	;

commands: 
	commands command
	| command
 	;

command:
	forbidden
	| automaton
  	;


forbidden: 
	FORBIDDEN OEQ2 IDENT '.' '{' IDENT'}' ';' 
	{ 	
		string target=$6;
		State* st=aut->getState(target);
		if(st == NULL){
			yyerror(target+ "is not declared");
		}
		if(inputbound == 0){
			fprintf(stderr,"You should input an integer as the threshold!\n");
			exit(1);
		}
		hybridReach reach(aut, st->ID, inputbound);
		reach.check();
	}

automaton:
	AUTOMATON IDENT {aut=new Automaton($2);} automaton_body END 
	{	
		if(syntax_error||!aut->init()){
			fprintf(stderr,"Syntax Error!\n");
			exit(1);
		}
		if(VERBOSE_LEVEL>3)		
			aut->print();					
		$$=aut;
	}
	;

automaton_body:
	declaration location_list initial
	;

declaration:
	|
	declaration vars {aut->vars=*$2;delete $2;}
	| declaration synclab
	;

synclab:
	SYNCLABS ':' ident_list ';' 	
	;

ident_list: 
	ident_list ',' IDENT  
        {    
        }
	| IDENT 
        {          
        }
	;	
vars:
	VAR ':' var_list ';'
	{
		$$=$3;
	}
	;


var_list: var_list ',' IDENT 
	{
		$$=$1; 
		$$->push_back($3); 
	}
	|IDENT 
	{  
		$$=new vector<string>();
		$$->push_back($1);
	}
	;					
						
initial:
	INITIALLY ':' initial_state ';' 
	; 

initial_state:
	IDENT 
	{ 
		State* st=aut->getState($1);
		if(st == NULL)
			yyerror(string($1)+" is not declared");
		else{		
			st->is_init=true;			
		}
	}
 		
  	;

location_list:
	location_list location_block
	|
	;

location_block:
	location transition_list
	{
		aut->states.push_back(*$1);		
		for(unsigned i=0;i<$2->size();i++){
			(*$2)[i].from=$1->name;
			aut->transitions.push_back((*$2)[i]);
		}	
		delete $1;
		delete $2;
	}
	;
location: 
	LOC IDENT ':' WHILE invariant_set WAIT '{' ODES '}'  
	{ 
		$$=new State($2);		
		if($5 != NULL){
			$$->invariants=*$5;
			delete $5;
		}				
		for(unsigned i=0;i<aut->vars.size();i++){		
			bool succ=false;
			for(unsigned j=0;j<$8->size();j++){			
				if((*$8)[j].var == aut->vars[i]){									
					succ=true;
					break;
				}
			}
			if(!succ){
				yyerror("Error in location:"+(string)$2+": every continuous variable must have solution!");
				break;
			}				
		}
		$$->ODEs=*$8;
		delete $8;
	}
	;

transition_list: 
	transition_list transition
	{
		$$=$1;
		$$->push_back(*$2);
		delete $2;
	}	
	|{$$=new vector<Transition>();}
	;
  
transition:
	WHEN guard_set SYNC IDENT DO '{' assign_set '}' GOTO IDENT ';'
	{ 
		$$=new Transition($10,$4);
		if($2 != NULL){
			$$->guards=*$2;
			delete $2;
		}
		$$->resets = *$7;
		delete $7;
	}

	|WHEN guard_set SYNC IDENT GOTO IDENT ';'
	{ 
		$$=new Transition($6,$4);
		if($2 != NULL){
			$$->guards=*$2;
			delete $2;
		}
	}
 
	;

assign_set:
	assign_set '&' assign_set_no_and 
	{
		$$=$1;
		$$->push_back(*$3);
		delete $3;
	}
	|assign_set_no_and 
	{
		$$=new vector<resetMap>();
		$$->push_back(*$1);
		delete $1;
	}
	;
assign_set_no_and: 
	IDENT PRIM ASSIGN polynomial
	{
		check_var($1);	
		$$=new resetMap($1,*$4);
		
	}
	;

invariant_set:
	constr_list
	{ 
		$$=$1;
	}
	;
/*	
invariant_no_and '&' invariant_set
	{ 
		$$=$3;
		if($1!=NULL){
			$$->push_back(*$1);
			delete $1;
		}
	}
	|invariant_no_and
	{
		$$=new vector<PolynomialConstraint>();
		if($1 != NULL){
			$$->push_back(*$1);
			delete $1;
		}
	}
	;
invariant_no_and:
	ODEpolynomial OGE NUM
	{
		$$=new PolynomialConstraint(*$1,GE,$3);
		delete $1;	
	}
	|ODEpolynomial OLE NUM	
	{	
		$$=new PolynomialConstraint(*$1,LE,$3);
		delete $1;
	}
	|ODEpolynomial OGT NUM	
	{
		$$=new PolynomialConstraint(*$1,GT,$3);
		delete $1;	
	}
	|ODEpolynomial OLT NUM	
	{
		$$=new PolynomialConstraint(*$1,LT,$3);
		delete $1;
	}
	|ODEpolynomial OEQ NUM	
	{	
		$$=new PolynomialConstraint(*$1,EQ,$3);
		delete $1;	
	}
	|TRUE {$$ = NULL;}
	;
*/
guard_set:
	constr_list
	{ 
		$$=$1;
	}
	;
constr_list:
	constr_list_no_and '&' constr_list
	{ 
		$$=$3;
		if($1!=NULL)
			$$->push_back(*$1);
		delete $1;
	}
	| constr_list_no_and
	{
		$$=new vector<PolynomialConstraint>();
		if($1!=NULL){		
			$$->push_back(*$1);
			delete $1;
		}
	}
	|'(' constr_list ')'
	{
		$$=$2;
	}
	;

constr_list_no_and:
	constraint
	{ 	
		$$=$1;
	}
   	;
   
constraint:
	polynomial OGE NUM
	{
		$$=new PolynomialConstraint(*$1,GE,$3);
		delete $1;	
	}
	|polynomial OLE NUM	
	{	
		$$=new PolynomialConstraint(*$1,LE,$3);
		delete $1;
	}
	|polynomial OGT NUM	
	{
		$$=new PolynomialConstraint(*$1,GT,$3);
		delete $1;	
	}
	|polynomial OLT NUM	
	{
		$$=new PolynomialConstraint(*$1,LT,$3);
		delete $1;
	}
	|polynomial OEQ NUM	
	{	
		$$=new PolynomialConstraint(*$1,EQ,$3);
		delete $1;	
	}
	|TRUE {$$ = NULL;}
;


polynomial:
polynomial '+' polynomial
{
	$$ = $1;
	(*$$) += (*$3);
	delete $3;
}
|
polynomial '-' polynomial
{
	$$ = $1;
	(*$$) -= (*$3);
	delete $3;
}
|
'(' polynomial ')'
{
	$$ = $2; 
}
|
polynomial '*' polynomial
{
	$$ = $1;
	(*$$) *= (*$3);
	delete $3;
}
|
polynomial '^' NUM
{
	int exp = atoi($3);
	if(exp == 0){
		Number I("1");
		int numVars = aut->dimension();
		$$ = new Polynomial(I,numVars );
	}
	else
	{
		$$ = new Polynomial(*$1);
		for(int i=1; i<exp; ++i)
		{
			(*$$) *= (*$1);
		}
	}
	delete $1;
}
|
'-' polynomial %prec uminus
{
	$$ = $2;
	$$->inv_assign();
}
|
IDENT
{	
	int id = check_var($1);
	int numVars = aut->dimension();
	Number I("1");
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[id] = 1;
	Monomial monomial(I, degrees);
	$$ = new Polynomial(monomial);
	delete $1;
}
|
NUM
{
	int numVars = aut->dimension();
	Number I($1);
	$$ = new Polynomial(I, numVars);
}


;

ODES:ODES '&' ODEsolution
{
	$$=$1;
	$$->push_back(*$3);
	delete $3;
}
|ODEsolution
{	
	$$=new vector<Solution>();
	$$->push_back(*$1);
	delete $1;
}
;

ODEsolution:IDENT '(' IDENT ')' OEQ2 ODEpolynomial
{
	if(strcmp($3,"t")!=0)
		yyerror("solution should be a function of time t\n");
	check_var($1);
	$$ = new Solution($1,*$6);
	delete $6;
}
;

ODEpolynomial: ODEpolynomial '+' ODEpolynomial
{
	$$ = $1;
	(*$$) += (*$3);
	delete $3;
}
|
ODEpolynomial '-' ODEpolynomial
{
	$$ = $1;
	(*$$) -= (*$3);
	delete $3;
}
|
'(' ODEpolynomial ')'
{
	$$ = $2; 
}
|
ODEpolynomial '*' ODEpolynomial
{
	$$ = $1;
	(*$$) *= (*$3);
	delete $3;
}
|
ODEpolynomial '^' NUM
{
	int exp = atoi($3);
	if(exp == 0)
	{
		Number I("1");
		$$ = new Polynomial(I, aut->dimension()+1);
	}
	else
	{
		$$ = new Polynomial(*$1);
		for(int i=1; i<exp; ++i)
		{
			(*$$) *= (*$1);
		}
	}

	delete $1;
}
|
'-' ODEpolynomial %prec uminus
{
	$$ = $2;
	$$->inv_assign();
}
|IDENT
{	
	if(strcmp($1,"t")!=0)
		yyerror("solution should be a function of time t\n");
	int numVars = aut->dimension()+1;
	Number I("1");
	vector<int> degrees;
	for(int i=0; i<numVars; ++i){
		degrees.push_back(0);
	}
	degrees[numVars-1] = 1;
	Monomial monomial(I, degrees);
	$$ = new Polynomial(monomial);
	
}
|IDENT '(' NUM ')'
{
	if(strcmp($3,"0")!=0)
		yyerror("only var(0) is permitted\n");
	if(strcmp($1,"t")==0)
		yyerror("t(0) is not permitted\n");
	int id = check_var($1);
	int numVars = aut->dimension()+1;
	Number I("1");
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[id] = 1;
	Monomial monomial(I, degrees);
	$$ = new Polynomial(monomial);
}
|NUM
{
	int numVars = aut->dimension()+1;
	Number I($1);
	$$ = new Polynomial(I, numVars);

}
;

%%
