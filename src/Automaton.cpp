#include "Automaton.h"


// class PolynomialConstraint
PolynomialConstraint::PolynomialConstraint(){}

PolynomialConstraint::PolynomialConstraint(Polynomial& _p,Operator _op, const char* _value):p(_p),op(_op),value(_value){

}

PolynomialConstraint::PolynomialConstraint(Polynomial& _p,Operator _op, const Number & _value):p(_p),op(_op),value(_value){

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

string PolynomialConstraint::toString(){
	string result="Constraint: "+p.toString();
	switch(op){
		case LT:result+="<";break;
		case LE:result+="<=";break;
		case EQ:result+="==";break;
		case GT:result+=">";break;
		case GE:result+=">=";break;
		default:fprintf(stderr,"unsupported operator");
	}
	result += value.toString();
	return result;
}


//class resetMap
resetMap::resetMap(string _var,Polynomial& _p):var(_var),p(_p){}

string resetMap::toString(){
	string result="reset "+var+" := ";
	result+=p.toString();
	return result;
}

Solution::Solution(string _var,Polynomial& _p):var(_var),p(_p){}

string Solution::toString(){
	string result="Solution:"+var+"(t)="+p.toString();
	return result;
}

//class State
State::State(string _name):name(_name){
	is_init=false;
}

void State::addInvariant(PolynomialConstraint& _p){
	invariants.push_back(_p);
}

string State::toString(){
	string result="State: "+name+" ID: "+int2string(ID)+"\n";
	if(is_init)result+="init state\n";
	for(unsigned i=0;i<invariants.size();i++)
		result+=invariants[i].toString()+"\n";
	for(unsigned i=0;i<ODEs.size();i++)
		result+=ODEs[i].toString()+"\n";
	return result;
}

//class Transition
Transition::Transition(string _to,string _label):to(_to),label(_label){}

string Transition::toString(){
	string result="Transition: "+label+" ID: "+int2string(ID)+" source: "+from+" target: "+to+"\n";
	for(unsigned i=0;i<guards.size();i++)
		result+=guards[i].toString()+"\n";
	for(unsigned i=0;i<resets.size();i++)
		result+=resets[i].toString()+"\n";
	return result;
}

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
bool Automaton::is_state(const int ID){
	assert(ID>=0);
	if((unsigned)ID<states.size())
		return true;
	return false;
}
string Automaton::nodeName(const int ID){
	if(is_state(ID)){
		State* st=getState((unsigned)ID);
		assert(st!=NULL);
		return st->name;
	}
	Transition* trans=getTransition((unsigned)ID);
	assert(trans!=NULL);
	return trans->label;
}


int Automaton::dimension(){
	return (int)vars.size();
}

bool Automaton::init(){
	int count=1;
	for(unsigned i=0;i<states.size();i++){
		State& st=states[i];
		substitute_invariant(st);
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
/* TODO  */
void Automaton::substitute_invariant(State& st){
//	for(unsigned i=0;i<invariants.size();i++){
//		Polynomial& p = invariants[i].p;
}		




/* print detailded information of the automaton */
void Automaton::print(){
	printf("Automaton: %s\nvar:",_name.c_str());
	for(unsigned i=0;i<vars.size();i++)
	  printf(" %s",vars[i].c_str());
	printf("\n");
	for(unsigned i=0;i<states.size();i++)
	  printf("%s\n",states[i].toString().c_str());
	for(unsigned i=0;i<transitions.size();i++)
	  printf("%s\n",transitions[i].toString().c_str());

}

