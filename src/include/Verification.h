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
	z3::expr_vector problem;

	z3::expr_vector encode_path(vector<int> path);
	z3::expr time(int state_index);
	z3::expr var(int var_index, int state_index, bool prime);
	z3::expr switch_op(z3::expr exp, Operator op, string value);
	z3::expr previous_var(vector<Constraint> reset_list, int var_id, int j);
	bool analyze_unsat_core(SubsetSolver& csolver, MapSolver& msolver);
	void add_IIS(IndexPair index);
	std::vector<IndexPair> index_cache; 
	std::vector<IndexPair> core_index; 	
	void clear();
public:
	Verification(Automaton* _ha);
	bool check_path(vector<int> path);
	vector<IndexPair> get_core_index(){return core_index;}
};




#endif
