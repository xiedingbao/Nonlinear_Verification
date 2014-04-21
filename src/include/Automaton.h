#ifndef _AUTOMATON_H
#define _AUTOMATON_H
#include "Polynomial.h"
#include <vector>
#include <cassert>
#include <stdio.h>
#include <string>

using namespace std;

enum Operator{LT,LE,GT,GE,EQ};

class PolynomialConstraint{
public:
	Polynomial p;
	Operator op;
	string value;
	PolynomialConstraint();
	PolynomialConstraint(Polynomial& _p,Operator op,string value);
	PolynomialConstraint(const PolynomialConstraint& pc);
	PolynomialConstraint& operator = (const PolynomialConstraint& _pc); 
	~PolynomialConstraint();
};

class resetMap{
public:
	string var;
	Polynomial p;
	resetMap(string var,Polynomial& _p);
};

class Solution{
public:
	string var;
	Polynomial p;
	Solution(string _var,Polynomial& _p);
};


class Transition;

class State{
public:
	string name;
	int ID;
	vector<Transition*> nextTrans;
	vector<PolynomialConstraint> invariants;
	vector<Solution> ODEs;
	bool is_init;

	State (string _name);
	void addInvariant(PolynomialConstraint& _p);
};

class Transition{
public:
	string from,to,label;
	int ID;
	State* sourceState;
	State* targetState;
	vector<PolynomialConstraint> guards;
	vector<resetMap> resets;

	Transition(string _to, string _label);
};

class Automaton{
private:
	string _name;
public:
	State* initState;
	vector<State> states;
	vector<Transition> transitions;
	vector<string> vars;

	Automaton(string name);
	string name();
	bool init();
	void print();
	State* getState(unsigned ID);
	Transition* getTransition(unsigned ID);
	State* getState(string name);
	Transition* getTransition(string name);
	int getIDForVar(string name);
	int dimension();
};


#endif
