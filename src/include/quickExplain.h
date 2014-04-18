#ifndef _QUICKEXPLAIN_H
#define _QUICKEXPLAIN_H
#include "z3++.h"
#include<vector>
#include<stdio.h>

/**
 * implements the QUICKEXPLAIN algorithm on top of z3(extract an unsat core from a set of nonlinear constraints)
 * Author:Dingbao Xie
 * 2013/04/18
 * */

class quickExplain{
private:
//	z3::expr_vector problem;
	z3::context& c;
	z3::solver s;
	std::vector<unsigned> empty;
	unsigned n;
	std::vector<unsigned> all_n;
	bool* selector;	
	bool solve(std::vector<unsigned> constraints);
	std::vector<unsigned> explain(std::vector<unsigned> B,std::vector<unsigned> C1,std::vector<unsigned> C2);
	void split(std::vector<unsigned>& C1,std::vector<unsigned>& C2,const std::vector<unsigned>& C);
	std::vector<unsigned> union_set(const std::vector<unsigned>& C1,const std::vector<unsigned>& C2);
	z3::expr c_var(unsigned i);
	void add_c_lits(z3::solver& s,const std::vector<unsigned>& constraints);
	void clear_selector();
public:
	quickExplain(z3::expr_vector problem, z3::context& _c);
	std::vector<unsigned> extract_core();
	~quickExplain();

	



};

#endif
