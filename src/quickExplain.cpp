#include "quickExplain.h"
using namespace z3;
using namespace std;


bool contain(const vector<unsigned>& list,const unsigned element){
	for(unsigned i=0;i<list.size();i++){
		if(list[i] == element)
		  return true;
	}
	return false;
}

/* constructor of quickExplain */
quickExplain::quickExplain(expr_vector _problem,context& _c):c(_c),s(_c){
	n = _problem.size();
	for(unsigned i=0;i<_problem.size();i++){
		s.add(implies(c_var(i),_problem[i]));
		all_n.push_back(i);
	}
	selector=new bool[n];
}
/*retrieve an unsat core from a set of nonlinear constraints */
vector<unsigned> quickExplain::extract_core(){
	if(solve(all_n))
		return empty;
	return explain(empty,empty,all_n);
}

vector<unsigned> quickExplain::explain(vector<unsigned> B,vector<unsigned> delta,vector<unsigned> C){
	if(delta.size()!=0 && !solve(B))
		return empty;
	if(C.size() == 1)
		return C;
	vector<unsigned> C1,C2;
	split(C1,C2,C);
	vector<unsigned> delta2=explain(union_set(B,C1),C1,C2);
	vector<unsigned> delta1=explain(union_set(B,delta2),delta2,C1);
	return union_set(delta1,delta2);
}

/* check the satisfiability of a subset of the whole constraints (incremental solving)*/
bool quickExplain::solve(vector<unsigned> constraints){
	s.push();
	add_c_lits(s,constraints);
	check_result result=s.check();
	cout<<s<<"\n"<<result<<"\n";
	assert(result!=unknown);
	s.pop();
	return result;
}

void quickExplain::split(vector<unsigned>& C1,vector<unsigned>& C2,const vector<unsigned>& C){
	unsigned median = C.size()/2;
	for(unsigned i=0;i<C.size();i++){
		if(i<median)
			C1.push_back(C[i]);
		else
			C2.push_back(C[i]);
	}
}

vector<unsigned> quickExplain::union_set(const vector<unsigned>& C1,const vector<unsigned>& C2){
	vector<unsigned> C=C1;
	clear_selector();
	for(unsigned i=0;i<C.size();i++)
		selector[C[i]]=true;
	for(unsigned i=0;i<C2.size();i++){
		if(!selector[C2[i]])
			C.push_back(C2[i]);
	}
	return C;
}


/* solving the subset of constriants in an incremental way */ 
void quickExplain::add_c_lits(solver& s,const vector<unsigned>& constraints){
	clear_selector();
	for(unsigned i=0;i<constraints.size();i++)
		selector[constraints[i]]=true;
	for(unsigned i=0;i<all_n.size();i++){
		if(selector[all_n[i]])
			s.add(c_var(all_n[i]));
		else
			s.add(!c_var(all_n[i]));
	}

}

expr quickExplain::c_var(unsigned i){
	char ch[256];
	sprintf(ch,"%d",i);
	return c.bool_const(ch);
}
void quickExplain::clear_selector(){
	for(unsigned i=0;i<n;i++)
		selector[i]=false;
}

quickExplain::~quickExplain(){
	if(selector!=NULL)
		delete[] selector;
}
