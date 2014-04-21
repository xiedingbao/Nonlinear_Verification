%{
	#include <stdio.h>
	#include <stdlib.h>
	#include "Automaton.h"

	#define DEBUG false

	bool syntax_error=false;
	extern int yylex();
	extern int inputbound;
  	extern unsigned int line_number;
	Automaton *aut;	
	string target;

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
		int id = aut->getIDForVar(name);
		if(id < 0){
			yyerror("Unknown identifier '" + name +"'.");;
			exit(1);
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
%token AND
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
		target=$6;
		State* st=aut->getState(target);
		if(st==NULL){
			yyerror("The target is not a location of the automaton!");
			exit(1);
		}
		if(inputbound == 0){
			fprintf(stderr,"You should input an integer as the threshold!\n");
			exit(1);
		}

	}

automaton:
	AUTOMATON IDENT {aut=new Automaton($2);} automaton_body END 
	{
		if(syntax_error||!aut->init()){
			fprintf(stderr,"Syntax Error!\n");
			exit(1);
		}
		if(DEBUG)		
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
	| IDENT 
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
		State* st=NULL;
		for(unsigned i=0;i<aut->states.size();i++){
			if(aut->states[i].name == $1){
				st = &aut->states[i];
				break;
			}
		}
		if(st == NULL)
			yyerror("The intial location is not declared");
		else{		
			st->is_init=true;			
		}
	}
 		
  	;

location_list:
	location_list location_block
	|location_block
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
	|location ';' transition_list
	;
	
location: 
	LOC IDENT ':' WHILE invariant_set WAIT '{' ODES '}'  
	{ 
		$$=new State($2);		
		if($5!=NULL){
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
		if($2!=NULL){
			$$->guards=*$2;
			delete $2;
		}
		$$->resets = *$7;
		delete $7;
	}

	| WHEN guard_set SYNC IDENT GOTO IDENT ';'
	{ 
		$$=new Transition($6,$4);
		if($2!=NULL){
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
	|TRUE{$$=NULL;}
	;
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
		if($1!=NULL)		
			$$->push_back(*$1);
		delete $1;
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


polynomial: polynomial '+' polynomial
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
	if(exp == 0)
	{
		int I = 1;
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
	int I = -1;
	$$ = $2;
	$$->mul_assign(I);
}
|
IDENT
{	
	int id = check_var($1);
	int numVars = aut->dimension();
	int I=1;
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
	int I = atoi($1);
	$$ = new Polynomial(I, numVars);
}
;

ODES:ODES AND ODEsolution
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

ODEsolution:IDENT '(' 't' ')' OEQ2 ODEpolynomial
{
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
		int I=1;
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
	int I = -1;
	$$ = $2;
	$$->mul_assign(I);
}
|'t'
{
	int numVars = aut->dimension()+1;
	int I = 1;
	vector<int> degrees;
	for(int i=0; i<numVars; ++i)
	{
		degrees.push_back(0);
	}
	degrees[numVars-1] = 1;
	Monomial monomial(I, degrees);
	$$ = new Polynomial(monomial);
	
}
|IDENT '(' '0' ')'
{
	int id = check_var($1);
	int numVars = aut->dimension()+1;
	int I = 1;
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
	int I = atoi($1);
	$$ = new Polynomial(I, numVars);
}
;

%%
