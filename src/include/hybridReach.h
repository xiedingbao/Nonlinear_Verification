#ifndef _HYBRISREACH_H
#define _HYBRIDREACH_H
#include "Automaton.h"
#include "minisat/core/Solver.h"
#include "Verification.h"

class hybridReach{
public:
	hybridReach(Automaton* aut, int target, int bound);
	bool check();
	~hybridReach();
private:
	Automaton* automaton;
	int target;
	int bound;
	std::string reachPath;
	int* traversedPath;
	unsigned num_of_path;
	std::string target_name;
	Verification verify;
	Minisat::Solver s;

	bool solve();
	void encode_graph();
	Minisat::Lit var(const int loop, const int ID);
	void decode(int code, int& loop, int& ID);
	std::string get_path_name(std::vector<int> path);
	void block_path(std::vector<int> path);
	std::vector<int> decode_path();
};


#endif
