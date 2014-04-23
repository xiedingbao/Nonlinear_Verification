#include "hybridReach.h"
using namespace minisat


hybridReach:hybridReach(Automaton* aut, int _target, int _bound):automaton(aut),target(_target),bound(_bound)verify(aut){i
	this->target_name = automaton->getNodeName(target);
	num_of_path=0;
}

/* Bounded reachability analysis return false:unreachable true:reachable */
bool hybridReach::check(){
	encode_graph();
	bool result = solve();
	if(result){
		printf("%s is reachable\nCounterexample: %s\n",target_name.c_str(),reachPath.c_str());
	}
	else {
		printf("%s is not reachable under bound %i\n",target_name.c_str(),bound);
	}
	printf("Number of path checked: %d\n", num_of_path);
	return result;
}


/* return true:reachable false:unreachable  */
bool hybridReach::solve(){
	for(int i=0;i<=bound;i++){
		while(true){
			if(s.solve(var(i,target))){
				num_of_path++;
				vector<int> path=decode_path();
				if(verify.check_path(path)){   //the path is feasible, terminate
					reachPath=get_path_name(path,true);
					return true;
				}
				else				//infeasible, feed the IIS path to the SAT solver
					block_path(path);
			}
			else
				break;
		}
	}
	return false;
}

/* extract the infeasible path segement and feed to the SAT solver */
void  hybridReach::block_path(vector<int> path){
	vector<IndexPair> indexs = verify.get_core_index();
	for(unsigned m=0;m<indexs.size();m++){
		int pathStart = indexs[m].start;
		int pathEnd   = indexs[m].end;
		vector<int> pathsegment;
		for (int i=pathStart;i<pathEnd; i++) {
			pathsegment.push_back(path[2*i]);
			pathsegment.push_back(path[2*i+1]);			
		}
		pathsegment.push_back(path[2*pathEnd]);
		if(VERBOSE_LEVEL>0){			
			cout<<"IIS Path: "<<get_path_name(pathsegment,false)<<endl;
		}			
		int loop = bound-(pathEnd-pathStart);
		for(int i=0;i<=loop;i++){
			Minisat::vec<Minisat::Lit> lits;
			for(unsigned int j=0;j<pathsegment.size();j++){
				lits.push(~var(i+j/2,pathsegment[j]));		
			}
			s.addClause(lits);			
		}
	}
}

/*encode the bounded graph structure of LHA into a propositional formula set*/
void hybridreach::encode_graph(){
	Minisat::vec<Minisat::Lit> lits;
	//initial condition	
	for(unsigned i=0;i<automaton->states.size();i++){
		State& st = automaton->states[i];
		if(st.is_init)
			s.addClause(var(0,st.ID));
		else
			s.addClause(~var(0,st.ID));
	}			
	//not exactly in one location and transition, exclude condition
	for(int k=0;k<=bound;k++){
		for(unsigned i=0;i<automaton->states.size();i++){
			for(unsigned j=i+1;j<automaton->states.size();j++){
				s.addClause(~var(k,automaton->states[i].ID), ~var(k,automaton->states[j].ID));
			}
		}
		for(unsigned i=0;i<automaton->transitions.size();i++){
			for(unsigned j=i+1;j<automaton->transitions.size();j++){
				s.addClause(~var(k,automaton->transitions[i].ID), ~var(k,automaton->transitions[j].ID));
			}
		}
	}
	// transition relation 
	for(unsigned int i=0;i<automaton->states.size();i++){
		State& st = automaton->states[i];			
		for(int k=0;k<bound;k++){
			Minisat::Lit x=var(k, st.ID);
			if(st.nextTrans.size() == 0){
				s.addClause(~x,var(k+1, st.ID));
				for(unsigned j=0;j<automaton->transitions.size();j++){
					s.addClause(~x, ~var(k,automaton->transitions[j].ID));
				}
			}
			else{	
				lits.clear();
				for(unsigned j=0;j<st.nextTrans.size();j++){
					Minisat::Lit next_tran_exp=var(k,st.nextTrans[j]->ID);
					Minisat::Lit next_state_exp=var(k+1,st.nextTrans[j]->toState->ID);
					s.addClause(~x, ~next_tran_exp, next_state_exp);
					lits.push(next_tran_exp);
				}
				lits.push(~x);
				s.addClause(lits);
			}
		}
	}
	//target condition
	lits.clear();
	for(int i=0;i<=bound;i++)
		lits.push(var(i, target));
	s.addClause(lits);
}

/* decode a path from a satisfiable model */
vector<int>  hybridReach::decode_path(){
	assert(s.okay());
	int state_num=automaton->states.size()+automaton->transitions.size();;
	int* path=new int[2*bound+1];
	for (int i=1;i<=state_num*(bound+1); i++) {
		if(s.modelValue(i) == Minisat::l_True){
			int id,loop;
			decode(i,loop,id);
			if(automaton->is_state(id))
				path[2*loop]=id;
			else
				path[2*loop+1]=id;
		}
	}
	vector<int> compress_path;
	for(int i=0;i<2*bound+1;i++){
		compress_path.push_back(path[i]);
		if(path[i] == target)
		  break;
	}
	if(VERBOSE_LEVEL>0)
		printf("checking path: %s\n",get_path_name(compress_path, false).c_str());
	delete[] path;
	return compress_path;
}

/**
 * @return the name of the path
 * @param path:sequence of node id
 * @param flag:true:ignore the final node ,false not ignore
 */
string hybridReach::get_path_name(vector<int> path){
	assert(path.size()%2!=0);
	string name="";
	unsigned path_len = path.size();
	for(unsigned i=0;i<path_len;i++){
		if(i%2==0)
			name+=automaton->getState(path[i])->name;
		else
			name+=automaton->getTransition(path[i])->label;
		if(i != path_len-1)
		  name += "^";
	}
	return name;
}
Minisat::Lit hybridReachn::var(const int loop, const int st){
	int state_num=automaton->states.size()+automaton->transitions.size();;
	int var= state_num*loop+st+1;
	while (var >= s.nVars()-1) s.newVar();
	return Minisat::mkLit(var);
}

void hybridReach::decode(int code,int& loop,int& ID){
	code--;
	int state_num=automaton->states.size()+automaton->transitions.size();;
	loop = code/state_num;
	ID = code%state_num;
}

