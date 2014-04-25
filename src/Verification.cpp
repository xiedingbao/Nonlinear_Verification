#include "Verification.h"
using namespace z3;
using namespace std;


/* constructor */
Verification::Verification(Automaton* ha):automaton(ha){

}

void Verification::clear(){
	index_cache.clear();
	core_index.clear();
}

/* verify the feasibility of a path
 * return true:feasible false:infeasible  
 * */
bool Verification::check_path(vector<int> path){
	clear();
	try{
		expr_vector problem=encode_path(path);
		if(VERBOSE_LEVEL>2)cout<<problem<<endl;
		quickExplain solver(problem,c);
		vector<unsigned> core=solver.extract_core();
		if(core.size() == 0)
			return true;
		else{
			analyze_unsat_core(core,problem);
		}
  	}
   	catch (z3::exception ex) {
		cerr << "Error: " << ex << endl;
		exit(1);
	}
	return false;
}


/* encode an abstract path into an nonlinear costraint set */
expr_vector Verification::encode_path(vector<int> patharray){
	int state_num = (patharray.size()+1)/2;
	expr_vector problem(c);
	// add the timing constraint: t>=0
	for(int i=1;i<state_num; i++) {
		addConstraint(problem,time(i)>=0,i,i);
	}
	for(int i=1;i<state_num; i++){		
		State* st=automaton->getState(patharray[2*i]);
		Transition* pre=automaton->getTransition(patharray[2*i-1]);
		assert(st!=NULL && pre!=NULL);
		//encode the constraitn for the continuous evolution of each variable
		encode_ODE(problem,st,i);	
	    //encode the invariant of current location(forall t invariant stands)
		encode_invariant(problem,st,i);
		//encode constraints related to the transition
		encode_transition(problem,pre,i);
	}
	return problem;
}

void Verification::encode_ODE(expr_vector& problem, State* st, int index){
	expr_vector domain(c);
	for(unsigned i=0;i<automaton->vars.size();i++)
		domain.push_back(var(automaton->vars[i],index,false));
	domain.push_back(time(index));
	for(unsigned i=0;i<st->ODEs.size();i++){
		Solution& so=st->ODEs[i];
		expr left = var(so.var,index,true);
		Polynomial& p=so.p;
		expr right(c);
		if(p.monomials.size() == 0)
			right=c.real_val("0");
		else{
			right = p.intEval(domain);
		}
		addConstraint(problem,left==right,index,index);
	}
}

void Verification::encode_invariant(expr_vector& problem, State* st, int index){
	expr_vector domain_0(c),domain_t(c);
	for(unsigned i=0;i<automaton->vars.size();i++){
		 domain_0.push_back(var(automaton->vars[i],index,false));
		 domain_t.push_back(var(automaton->vars[i],index,false));
	}
	domain_0.push_back(c.real_val("0"));
	domain_t.push_back(time(index));
	for(unsigned i=0;i<st->invariants.size();i++){	
		PolynomialConstraint& pc=st->invariants[i];
		addConstraint(problem,switch_op(pc.p.intEval(domain_0),pc.op,pc.value),index,index);
		addConstraint(problem,switch_op(pc.p.intEval(domain_t),pc.op,pc.value),index,index);
		constant_derivative(pc.p.derivative(automaton->vars.size()),index,problem,domain_0,domain_t);
	}
}
		

void Verification::constant_derivative(Polynomial p,int index,expr_vector& problem,const expr_vector& domain_0,const expr_vector& domain_t){
	if(p.isConstant())
		return;
	expr positive=p.intEval(domain_0)>=0&&p.intEval(domain_t)>=0;
	expr negative=p.intEval(domain_0)<=0&&p.intEval(domain_t)<=0;
	addConstraint(problem,positive||negative,index,index);
	constant_derivative(p.derivative(automaton->vars.size()),index,problem,domain_0,domain_t);
}


void Verification::encode_transition(expr_vector& problem,Transition* pre,int index){
	expr_vector domain(c);
	for(unsigned i=0;i<automaton->vars.size();i++)
		 domain.push_back(var(automaton->vars[i],index-1,true));
	for(unsigned i=0;i<pre->guards.size();i++)
		addConstraint(problem,switch_op(pre->guards[i].p.intEval(domain),pre->guards[i].op,pre->guards[i].value),index-1,index);
	for(unsigned i=0;i<pre->resets.size();i++){
		expr var_prime=var(pre->resets[i].var,index,false);
		addConstraint(problem,var_prime==pre->resets[i].p.intEval(domain),index-1,index);
	}
	for(unsigned i=0;i<automaton->vars.size();i++){
		unsigned j;
		string _var=automaton->vars[i];
		for(j=0;j<pre->resets.size();j++){         //reset
			if(pre->resets[j].var == _var)
				break;
		}
		if(j == pre->resets.size()){                //x':=x after the transition
			addConstraint(problem,var(_var,index,false)==var(_var,index-1,true),index-1,index);
		}
	}

}

expr Verification::time(int state_index){
	string tname="t_"+int2string(state_index);
	return c.real_const(tname.c_str());
}

expr Verification::var(string var, int state_index, bool prime){
	string vname=var+"_"+int2string(state_index);
	if(prime)
		vname+="_prime";
	return c.real_const(vname.c_str());
}

expr Verification::switch_op(expr exp,Operator op,Number & value){
	expr val=c.real_val(value.toString().c_str());
	switch(op){
		case LT:return exp<val;
		case LE:return exp<=val;
		case GT:return exp>val;
		case GE:return exp>=val;
		case EQ:return exp==val;
	}
	return exp;
}

void Verification::addConstraint(expr_vector& problem, const expr& con, int start, int end){
	problem.push_back(con);
	index_cache.push_back(IndexPair(start,end));
}



void Verification::analyze_unsat_core(const vector<unsigned>& core, const expr_vector& problem){
	int from = INT_MAX, to = 0;
	if(VERBOSE_LEVEL>2) printf("unsat core:\n");
	for(unsigned i=0;i<core.size();i++){
		if(VERBOSE_LEVEL>2)cout<<problem[core[i]]<<"\n"; 
		int start = index_cache[core[i]].start;
		int end   = index_cache[core[i]].end;
		if(from>start)
			from = start;
		if(to<end)
			to = end;
	}
	add_IIS(IndexPair(from,to));
}

void Verification::add_IIS(IndexPair index){
	for(unsigned i=0;i<core_index.size();i++){
		if(index.contain(core_index[i])){
		  core_index[i] = index;
		  return;
		}
		else if(core_index[i].contain(index))
		  return;
	}
	core_index.push_back(index);
}



