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
//		cout<<problem<<endl;
		SubsetSolver csolver(c, problem);
		MapSolver msolver(csolver.size());
		if(!analyze_unsat_core(csolver, msolver))	
			return true;
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
			problem.push_back(time(i)>=0);
			index_cache.push_back(IndexPair(i,i));
	}
	for(int  i= 1;i<state_num; i++){		
		State* st=ha->getState(patharray[2*j]);
		Transition* pre=ha->getTransition(patharray[2*i-1]);
		assert(st!=NULL && pre!=NULL);
		//encode the flow condition
		encode_ODE(problem,st,i);	
	    //encode the invariant of current location	and lamda_x
		encode_invariant(problem,st,i);

		for(unsigned m=0;m<st->invariantList.size();m++){
			Constraint* con = &st->invariantList[m];
			expr invariant_exp1(c);
			expr invariant_exp2(c);	
			for(unsigned n=0;n<con->pvlist.size();n++){
				const char* parameter = con->pvlist[n].parameter.c_str();
				expr pv_exp1 = c.real_val(parameter)*var(con->pvlist[n].var->id,j);
				expr pv_exp2 = c.real_val(parameter)*previous_var(pre->resetList,con->pvlist[n].var->id,j);
				if(n == 0){
					invariant_exp1=pv_exp1;	
					invariant_exp2=pv_exp2;
				}
				else{
					invariant_exp1=invariant_exp1+pv_exp1;
					invariant_exp2=invariant_exp2+pv_exp2;
				}
			}
			problem.push_back(switch_op(invariant_exp1,con->op,con->value));
			problem.push_back(switch_op(invariant_exp2,con->op,con->value));
			index_cache.push_back(IndexPair(j,j));
			index_cache.push_back(IndexPair(j-1,j));
		}
		//encode the previous transition guard	
		for(unsigned m=0;m<pre->guardList.size();m++){
			Constraint* con = &pre->guardList[m];
			expr guard_exp(c);
			for(unsigned n=0;n<con->pvlist.size();n++){
				ParaVariable pv=con->pvlist[n];
				expr pv_exp=var(pv.var->id,j-1)*c.real_val(pv.parameter.c_str());
				if(n == 0)
					guard_exp=pv_exp;
				else					
					guard_exp=guard_exp+pv_exp;
			}
			problem.push_back(switch_op(guard_exp,con->op,con->value));
			index_cache.push_back(IndexPair(j-1,j));
		}		
	}
	return problem;
}

void Verification::encode_ODE(const expr_vector& problem, State* st, int index){
	for(unsigned i=0;i<ODEs.size();i++){
		Solution& so=ODEs[i];
		expr left = var(so.var,index,true)-var(so.var,index,false);
		Polynomial& p=so.p;
		expr right(c);
		if(p.monomials.size() == 0)
			right=c.real_val("0");
		else{
			expr_vector domain(c);
			for(unsigned j=0;j<automaton->vars.size();j++)
			  domain.push_back(var(automaton->vars[k],index,false));
			domain.push_back(time(index));
			right = p.intEval(domain)
		}
/*	for(unsigned j=0;j<p.monomials.size();j++){
			Monnomial& mono=monomials[j];
			expr mono_exp=c.real_val(int2string(mono.coefficient).c_str());
			for(unsigned k=0;k<mono.degree.size();k++){
				if(mono.degree[k]!=0){
					expr v(c);
					if(k>=automaton->vars.size())
						v=time(index);
					else
						v=var(automaton->vars[k],index,false);
					for(int m=0;m<mono.degree[k];m++)
						mono_exp=mono_exp*v;
				}	
				
			}
			right+=mono_exp;
		}*/
		problem.push_back(left==right);
		index_cache.push_back(IndexPair(j,j));
	}
}
void Verification::encode_invariant(expr_vector& problem, State* st, int index){
	expr_vector domain_0(c);
	for(unsigned i=0;j<automaton->vars.size();j++)
		 domain_0.push_back(var(automaton->vars[i],index,false));
	expr_vector domain_t=domain_0;		
	domain_0.push_back(c.real_val("0"));
	domain_t.push_back(time(index));
	for(unsigned i=0;i<st->invariants.size();i++){	
		PolynomialCostraint& pc=invariants[i];
		problem.push_back(switch_op(pc.p.intEval(domain_0),pc.op,pc.value));
		index_cache.push_back(IndexPair(index,index));
		problem.push_back(switch_op(pc.p.intEval(domain_t),pc.op,pc.value));
		index_cache.push_back(IndexPair(index,index));
		constant_derivative(pc.p.derivative(),index,problem,domain_0,domain_t);
	}
}
		

void Verification::constant_derivative(Polynomial p,int index,const expr_vector& problem,const expr_vector& domain_0,const expr_vector& domain_t){
	if(p.isConstant())
		return;
	problem.push_back(p.intEval(domain_0));
	index_cache.push_back(IndexPair(index,index));
	problem.push_back(pc.p.intEval(domain_t));
	index_cache.push_back(IndexPair(index,index));
	constant_derivative(p.derivative(),index,problem,domain_0,domain_t);
}


expr Verification::previous_var(vector<Constraint> reset_list,int var_id,int j){
	expr pre_var=var(var_id,j-1);
	for(unsigned int i=0;i<reset_list.size();i++){
		if(reset_list[i].pvlist[0].var->id == var_id){
			pre_var=c.real_val(reset_list[i].value.c_str());	
			break;
		}
	}
	return pre_var;
}

expr Verification::time(int state_index){
	string tname="t_"+int2string(state_index);
	return c.real_const(tname.c_str());
}

expr Verification::var(string var, int state_index, bool prime){
	string vname="v_"+var+"_"+int2string(state_index);
	if(prime)
		vname+="_prime";
	return c.real_const(vname.c_str());
}

expr Verification::switch_op(expr exp,Operator op,int value){
	expr val=c.real_val(int2string(value).c_str());
	switch(op){
		case LT:return exp<val;
		case LE:return exp<=val;
		case GT:return exp>val;
		case GE:return exp>=val;
		case EQ:return exp==val;
	}
	return exp;
}

/* analyze the unsat core to extract the infeasible path segment */
bool Verification::analyze_unsat_core(SubsetSolver& csolver, MapSolver& msolver){
	for(int k=0;k<MUS_LIMIT;k++){
		vector<int> seed = msolver.next_seed();
		if(seed.size() == 0)
			break;
		if(!csolver.check_subset(seed)){
			vector<int> MUS = csolver.shrink(seed);
			int from = INT_MAX, to = 0;
			if(VERBOSE_LEVEL>2) printf("MUS:\n");
			for(unsigned i=0;i<MUS.size();i++){
				if(VERBOSE_LEVEL>2) cout<<csolver.get_constraint(MUS[i])<<endl;
				int start = index_cache[MUS[i]].start;
				int end   = index_cache[MUS[i]].end;
				if(from>start)
					from = start;
				if(to<end)
					to = end;
			}
			add_IIS(IndexPair(from,to));
			if(UC_LEVEL == 0) break;
			msolver.block_up(MUS);
		}
		else{
			if(seed.size() == csolver.size())
				return false;
			msolver.block_down(seed);
		}
	}
	return true;
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



