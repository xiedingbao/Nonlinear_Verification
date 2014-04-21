#include "Automaton.h"


// class PolynomialConstraint
PolynomialConstraint::PolynomialConstraint(){}

PolynomialConstraint::PolynomialConstraint(Polynomial& _p,Operator _op,string _value){
	this->p=_p;
	this->op=_op;
	this->value=_value;
}

PolynomialConstraint::PolynomialConstraint(const PolynomialConstraint& _pc){
	p = _pc.p;
	op = _pc.op;
	value = _pc.value;
}
PolynomialConstraint& PolynomialConstraint::operator = (const PolynomialConstraint& pc){
	if(this == &pc)
		return *this;
	p = pc.p;
	op = pc.op;
	value = pc.value;
	return *this;
}
PolynomialConstraint::~PolynomialConstraint(){}

//class resetMap
resetMap::resetMap(string _var,Polynomial& _p):var(_var),p(_p){}

Solution::Solution(string _var,Polynomial& _p):var(_var),p(_p){}

//class State
State::State(string _name):name(_name){}

void State::addInvariant(PolynomialConstraint& _p){
	invariants.push_back(_p);
}

//class Transition
Transition::Transition(string _to,string _label):to(_to),label(_label){}



//class Automaton
Automaton::Automaton(string name):_name(name){};

string Automaton::name(){
	return _name;
}

int Automaton::getIDForVar(string name){
	for(unsigned i=0;i<vars.size();i++){
		if(vars[i]==name)
			return (int)i;
	}
	return -1;
}

State* Automaton::getState(unsigned ID){
	assert(ID<states.size());
	return &states[ID];
}

State* Automaton::getState(string name){
	for(unsigned i=0;i<states.size();i++){
		if(states[i].name == name)
			return &states[i];
	}
	return NULL;
}

Transition* Automaton::getTransition(unsigned ID){
	assert(ID<transitions.size()+states.size());
	return &transitions[ID-states.size()];
}

Transition* Automaton::getTransition(string name){
	for(unsigned i=0;i<transitions.size();i++){
		if(transitions[i].label == name)
			return &transitions[i];
	}
	return NULL;
}


int Automaton::dimension(){
	return (int)vars.size();
}

bool Automaton::init(){
	int count=1;
	for(unsigned i=0;i<states.size();i++){
		State& st=states[i];
		st.nextTrans.clear();
		if(st.is_init){
			initState = &st;
			st.ID=0;
		}
		else
		  st.ID=count++;
		for(unsigned j=0;j<transitions.size();j++){
			Transition& tran=transitions[j];
			if(st.name==tran.from){
				st.nextTrans.push_back(&tran);
				tran.sourceState = &st;
			}
			if(st.name==tran.to){
				tran.targetState=&st;
			}
		}
	}
	for(unsigned i=0;i<transitions.size();i++){
		Transition& tran=transitions[i];
		tran.ID=count++;
		if(tran.targetState == NULL){
			fprintf(stderr,"Error: can not find the target state:%s of transition %s\n",tran.to.c_str(),tran.label.c_str());
			return false;
		}
		if(initState == NULL){
			fprintf(stderr,"Error: No init state\n");
			return false;
		}
	}
	return true;
}








/* print detailded information of the automaton */
void Automaton::print(){


}

