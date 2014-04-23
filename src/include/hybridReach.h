#ifndef _HYBRISREACH_H
#define _HYBRIDREACH_H
#include "Automaton.h"
#include "minisat/core/Solver.h"
#include "Verification.h"

class hybridReach{
public:
	hybridReach(Automaton* aut,int target,int bound);
	bool check();
	~hybridReach{}
private:
	Automaton* automaton;
	int target;
	int bound;
	string reachPath;
	int* traversedPath;
	unsigned num_of_path;
	string target_name;
	Verification verify;
	Minisat::Solver s;

	bool solve();
	void encode_graph();
	Minisat::Lit var(const int loop, const int ID);
	void decode(int code, int& loop, int& ID);
	string get_path_name(vector<int> path, bool flag);
	void block_path(vector<int> path);
	vector<int> decode_path();
};


#endif
