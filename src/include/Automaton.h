#ifndef _AUTOMATON_H
#define _AUTOMATON_H
#include "Polynomial.h"
#include <vector>
#include <cassert>
#include <stdio.h>
#include <string>
#include "general.h"
#include "Number.h"


using namespace std;

enum Operator{LT,LE,GT,GE,EQ};

class PolynomialConstraint{
public:
	Polynomial p;
	Operator op;
	Number value;
	PolynomialConstraint();
	PolynomialConstraint(Polynomial& _p, Operator op, const char* _value);
	PolynomialConstraint(Polynomial& _p, Operator op, const Number & _value);

	PolynomialConstraint(const PolynomialConstraint& pc);
	PolynomialConstraint& operator = (const PolynomialConstraint& _pc); 
	~PolynomialConstraint();
	string toString(const std::vector<std::string>& varNames);
};

class resetMap{
public:
	string var;
	Polynomial p;
	resetMap(string var,Polynomial& _p);
	string toString(const std::vector<std::string>& varNames);
};

class Solution{
public:
	string var;
	Polynomial p;
	Solution(string _var,Polynomial& _p);
	string toString(const std::vector<std::string>& varNames);
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
	string toString(const std::vector<std::string>& varNames);
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
	string toString(const std::vector<std::string>& varNames);


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
	void substitute_invariant(State& st);
	void print();
	State* getState(unsigned ID);
	Transition* getTransition(unsigned ID);
	State* getState(string name);
	Transition* getTransition(string name);
	int getIDForVar(string name);
	int dimension();
	bool is_state(const int ID);
	std::string nodeName(const int ID);
};


#endif
