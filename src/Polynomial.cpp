#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial(){}

Polynomial::Polynomial(const Monomial& monomial){
	monomials.push_back(monomial);
}

Polynomial::Polynomial(const Number & I,const int numVars){
	Number zero;
	if(I != zero){
		Monomial monomial(I, numVars);
		monomials.push_back(monomial);
	}
}

Polynomial::Polynomial(const vector<Monomial>& monos):monomials(monos){
	reorder();
}

Polynomial::Polynomial(const Polynomial & polynomial):monomials(polynomial.monomials)
{
}

Polynomial::~Polynomial()
{
	monomials.clear();
}

/* bubble sort */
void Polynomial::reorder(){
	unsigned n=monomials.size();
	for(unsigned i=0;i<n;i++){
		for(unsigned j=0;j<n-i-1;j++){
			if(monomials[j+1]<monomials[j]){
				Monomial temp=monomials[j];
				monomials[j]=monomials[j+1];
				monomials[j+1]=temp;
			}
		}
	}
}

void Polynomial::clear()
{
	monomials.clear();
}

void Polynomial::inv(Polynomial& result) const{
	result = *this;
	result.inv_assign();
}

void Polynomial::inv_assign(){
	for(unsigned i=0;i<monomials.size();i++)
		monomials[i].coefficient.inv_assign();;
}

void Polynomial::mul_assign(const Monomial & monomial){
//	printf("(%s) * (%s) = ",toString().c_str(),monomial.toString().c_str());

	Number zero;
	if(monomial.coefficient == zero){
		clear();
	}
	else{
		for(unsigned i=0;i<monomials.size();i++)
			monomials[i] *= monomial;
	}
//	printf("%s\n",toString().c_str());

}

void Polynomial::mul_assign(const Number & I){
	Number zero;
	if(I == zero)
		clear();
	else{
		vector<Monomial>::iterator iter;
		for(iter=monomials.begin();iter!=monomials.end(); ){
			iter->coefficient *= I;
			if(iter->coefficient==zero)
			  iter=monomials.erase(iter);
			else
			  iter++;
		}

	}
}

Polynomial & Polynomial::operator = (const Polynomial & polynomial){
	if(this == &polynomial)
		return *this;
	monomials = polynomial.monomials;
	return *this;
}

Polynomial & Polynomial::operator += (const Polynomial & polynomial){
	Polynomial result;
	unsigned i,j;
	for(i=0,j=0;;){
		if(i==monomials.size() || j==polynomial.monomials.size())
			break;
		if(monomials[i]<polynomial.monomials[j])
			result.monomials.push_back(monomials[i++]);
		else if(polynomial.monomials[j]<monomials[i])
			result.monomials.push_back(polynomial.monomials[j++]);
		else{
			Number coeffTemp = monomials[i].coefficient+polynomial.monomials[j].coefficient;
			Monomial monoTemp(monomials[i]);
			monoTemp.coefficient = coeffTemp;
			result.monomials.push_back(monoTemp);
			i++,j++;
		}
	}
	if(i==monomials.size() && j!=polynomial.monomials.size()){
		for(;j<polynomial.monomials.size();j++)
			result.monomials.push_back(polynomial.monomials[j]);
	}
	else if(i!=monomials.size() && j==polynomial.monomials.size()){
		for(;i<monomials.size();i++)
			result.monomials.push_back(monomials[i]);
	}
	*this = result;
	return *this;
}

Polynomial & Polynomial::operator -= (const Polynomial & polynomial){
	Polynomial polyTemp = polynomial;
	polyTemp.inv_assign();
	*this += polyTemp;
	return *this;
}

Polynomial & Polynomial::operator *= (const Polynomial & polynomial){
	Polynomial result;
	if((monomials.size()==0) || (polynomial.monomials.size()==0)){
		this->clear();
		return *this;
	}
	for(unsigned i=0;i<polynomial.monomials.size();i++){
		Polynomial polyTemp = *this;
		polyTemp.mul_assign(polynomial.monomials[i]);
		result += polyTemp;
	}
	*this = result;
	return *this;
}

const Polynomial Polynomial::operator + (const Polynomial & polynomial) const{
	Polynomial result = *this;
	result += polynomial;
	return result;
}

const Polynomial Polynomial::operator - (const Polynomial & polynomial) const{
	Polynomial result = *this;
	result -= polynomial;
	return result;
}

const Polynomial Polynomial::operator * (const Polynomial & polynomial) const{
	Polynomial result = *this;
	result *= polynomial;
	return result;
}


int Polynomial::degree() const{
	if(monomials.size() > 0)
		return monomials.back().d;
	else
		return 0;
}

bool Polynomial::isZero() const{
	if(monomials.size() == 0){
		return true;
	}
	else{
		return false;
	}
}

Polynomial Polynomial::derivative( const int varIndex) const{
	Polynomial result = *this;
	vector<Monomial>::iterator iter;	
	for(iter = result.monomials.begin(); iter != result.monomials.end(); ){
		if(iter->degrees[varIndex] > 0){
			int tmp = iter->degrees[varIndex];
			iter->degrees[varIndex] -= 1;
			iter->d -= 1;
			iter->coefficient *= Number(int2string(tmp).c_str());
			++iter;
		}
		else{
			iter = result.monomials.erase(iter);
		}
	}
	return result;
}
Number Polynomial::constant(){
	Number zero;
	if(monomials.size()>0 && monomials[0].d==0)
		return monomials[0].coefficient;
	return zero;
}

z3::expr Polynomial::intEval(const z3::expr_vector& domain)const{
	assert(domain.size()!=0);
	z3::context& c = domain[0].ctx();
	z3::expr exp = c.real_val("0");
	for(unsigned i=0;i<monomials.size();i++){
		exp = exp+monomials[i].intEval(domain);
	}
	return exp;
}


void Polynomial::substitute(const vector<Polynomial>& domain){
	Polynomial result;
	if((monomials.size()==0) || (domain.size()==0)){
		this->clear();
		return;
	}
	for(unsigned i=0;i<monomials.size();i++){
		result += substitute(monomials[i],domain);
	}
	*this = result;
	reorder();
}

Polynomial Polynomial::substitute(const Monomial & mono, const vector<Polynomial> & domain){
	assert(mono.dimension() == domain.size());
	Polynomial result(mono.coefficient, mono.dimension()+1);
	for(unsigned i=0;i<mono.degrees.size();i++){
		for(int j=0;j<mono.degrees[i];j++)
			result *= domain[i];
	}
	return result;
}

bool Polynomial::isConstant(){
	if(monomials.back().d==0)
		return true;
	return false;
}

string Polynomial::toString(const std::vector<std::string> varNames) const{
	string strPoly;
	if(monomials.size() == 0){
		return "0";
	}
	for(unsigned i=0;i<monomials.size();i++){
		strPoly += monomials[i].toString(varNames);
		if(i!=monomials.size()-1)
		  strPoly+=" + ";
	}
	return strPoly;
}


