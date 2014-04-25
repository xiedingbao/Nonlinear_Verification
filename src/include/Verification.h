#ifndef _verification_h
#define _verification_h
#include "Automaton.h"
#include "z3++.h"
#include "quickExplain.h"
#include <iostream>


class IndexPair{
public:
	int start;
	int end;
	IndexPair(int _start,int _end):start(_start),end(_end){}
	bool contain(IndexPair& index){return start>=index.start && end<=index.end;}
};


class Verification{
	Automaton* automaton;
	z3::context c;
	std::vector<IndexPair> index_cache; 
	std::vector<IndexPair> core_index; 	

	z3::expr_vector encode_path(vector<int> path);
	z3::expr time(int state_index);
	z3::expr var(std::string var_name, int state_index, bool prime);
	z3::expr switch_op(z3::expr exp, Operator op, Number & value);
	void encode_ODE(z3::expr_vector& problem, State* st, int index);
	void encode_invariant(z3::expr_vector& problem, State* st, int index);
	void constant_derivative(Polynomial p, int index, z3::expr_vector& problem, const z3::expr_vector& domain_0, const z3::expr_vector& domain_t);
	void encode_transition(z3::expr_vector& problem, Transition* pre, int index);
	void addConstraint(z3::expr_vector& problem, const z3::expr& exp, int start, int end);

	void analyze_unsat_core(const std::vector<unsigned>& core, const z3::expr_vector& problem);
	void add_IIS(IndexPair index);
	void clear();

public:
	Verification(Automaton* _ha);
	bool check_path(vector<int> path);
	vector<IndexPair> get_core_index(){return core_index;}
};




#endif
