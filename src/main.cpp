#include "z3++.h"
#include <stdio.h>
#include <iostream>
#include "quickExplain.h"
using namespace z3;
using namespace std;

int main(int argc, char *args[]){
	context c;
	expr x=c.real_const("x");
	expr y=c.real_const("y");
	expr z=c.real_const("z");
	solver s(c);
	params p(c);
//	p.set(":unsat-core",true);
//	p.set(":auto-config",false);
	s.set(p);
	expr p1=c.bool_const("p1");
	expr p2=c.bool_const("p2");
	expr p3=c.bool_const("p3");
	expr p4=c.bool_const("p4");
	expr p5=c.bool_const("p5");
	expr p6=c.bool_const("p6");
	expr p7=c.bool_const("p7");
	expr_vector assumptions(c);
	assumptions.push_back(2*x*x>=y*z);
	assumptions.push_back(x>100);
	assumptions.push_back(y<0);
	assumptions.push_back(z<0);
	assumptions.push_back(y*y>1234);
	assumptions.push_back(z*z*z<-25);
	assumptions.push_back(x<50);
	quickExplain explain(assumptions,c);
	vector<unsigned> core=explain.extract_core();
	printf("core: ");
	for(unsigned i=0;i<core.size();i++)
	  printf("%d ",core[i]);
	printf("\n");

/*	s.add(implies(p1,2*x*x>=y*z));
	s.add(implies(p2,x>100));
	s.add(implies(p3,y<0));
	s.add(implies(p4,z<0));
	s.add(implies(p5,y*y>1234));
	s.add(implies(p6,z*z*z<-25));
	s.add(implies(p7,x<50));
	std::cout<<s.check()<<"\n";
	model m=s.get_model();
	std::cout<<"solution:"<<m<<"\n";
	s.add(p1&&p2&&p3&&p4);
	s.push();
	s.add(p5&&p6&&p7);
	std::cout<<s<<"\n"<<s.check()<<"\n";
	s.pop();
	s.add(p5&&p6);
	std::cout<<s<<"\n"<<s.check()<<"\n";

//	std::cout<<s<<"\n";	
	switch(s.check()){
		case sat:printf("sat\n");break;
		case unsat:std::cout<<"unsat:"<<s.unsat_core()<<"\n";break;
		case unknown:printf("unknown\n");break;
	}*/
	return 0;
}
