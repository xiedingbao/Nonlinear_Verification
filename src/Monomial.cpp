#include "Monomial.h"
using namespace std;

Monomial::Monomial(){}

Monomial::Monomial(int I, const vector<int> & degs):coefficient(I), degrees(degs), d(0){
	for(unsigned i=0; i<degs.size(); ++i){
		d += degs[i];
	}
}

Monomial::Monomial(const Monomial & monomial): coefficient(monomial.coefficient), degrees(monomial.degrees), d(monomial.d)
{
}

Monomial::Monomial(const int I, const int numVars):d(0){
	for(int i=0; i<numVars; ++i){
		degrees.push_back(0);
	}
	coefficient = I;
}

Monomial::~Monomial(){
	degrees.clear();
}

int Monomial::degree() const{
	return d;
}

int Monomial::dimension() const{
	return degrees.size();
}


Monomial & Monomial::operator = (const Monomial & monomial){
	if(this == &monomial)
		return *this;
	coefficient = monomial.coefficient;
	degrees = monomial.degrees;
	d = monomial.d;
	return *this;
}

Monomial & Monomial::operator += (const Monomial & monomial){
	coefficient += monomial.coefficient;
	return *this;
}

Monomial & Monomial::operator *= (const Monomial & monomial){
	coefficient *= monomial.coefficient;
	for(unsigned i=0; i<degrees.size(); ++i){
		degrees[i] += monomial.degrees[i];
	}

	d += monomial.d;
	return *this;
}


bool Monomial::isLinear(int & index) const{
	if(d == 1){
		for(unsigned i=0; i<degrees.size(); ++i){
			if(degrees[i] == 1){
				index = i;
				return true;
			}
		}
	}

	return false;
}


z3::expr Monomial::intEval(const z3::expr_vector& domain)const{
//	cout<<domain<<"\n"<<flush;
//	printf(" coefficient: %i\n",coefficient);
//	for(unsigned i=0;i<degrees.size();i++)
//	  printf(" %i",degrees[i]);
//	cout<<"\n"<<flush;
	assert(domain.size()==degrees.size());
	z3::context& c=domain[0].ctx();
	z3::expr result=c.real_val(int2string(coefficient).c_str());
	for(unsigned i=0;i<degrees.size();i++){
		for(int j=0;j<degrees[i];j++)
			result=result*domain[i];
	}
	return result;
}


string Monomial::toString(){
	string strMono;
	strMono += '(';
	strMono += int2string(coefficient);
	for(unsigned i=0; i<degrees.size(); i++){
		if(degrees[i] != 0){
			if(degrees[i] == 1){
				strMono += ' ';
				strMono += '*';
				strMono += ' ';
			//	strMono += varNames[i];
				strMono +="var_"+unsigned2string(i);
			}
			else{
				strMono += ' ';
				strMono += '*';
				strMono += ' ';
			//	strMono += varNames[i];
				strMono +="var_"+unsigned2string(i);
				strMono += '^';
				strMono += unsigned2string(degrees[i]);
			}
		}
	}
	strMono += ')';
	return strMono;
}


bool operator == (const Monomial & a, const Monomial & b){
	if (a.d == b.d){
		for(unsigned i=0; i<a.degrees.size(); i++){
			if(a.degrees[i] != b.degrees[i])
				return false;
		}
		return true;	// The two monomials are identical without considering the coefficients.
	}
	else
		return false;
}

bool operator < (const Monomial & a, const Monomial & b){
	if(a.d < b.d)
		return true;
	else if(a.d > b.d)
		return false;
	else{	// a.d == b.d
		for(unsigned i=0; i<a.degrees.size(); ++i){
			if(a.degrees[i] < b.degrees[i])
				return true;
			else if(a.degrees[i] > b.degrees[i])
				return false;
		}
	}
	return false;	// a == b
}
