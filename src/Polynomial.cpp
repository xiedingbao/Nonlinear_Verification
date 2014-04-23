#include "Polynomial.h"

using namespace std;

Polynomial::Polynomial(){}


Polynomial::Polynomial(const Monomial& monomial){
	monomials.push_back(monomial);
}

Polynomial::Polynomial(const int I,const int numVars){
	if(I != 0){
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
//	monomials.sort();
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
	result=*this;
	result.inv_assign();
}
void Polynomial::inv_assign(){
	for(unsigned i=0;i<monomials.size();i++)
		monomials[i].coefficient=monomials[i].coefficient*-1;
}

void Polynomial::mul_assign(const Monomial& monomial){
	if(monomial.coefficient==0)
		clear();
	else{
		for(unsigned i=0;i<monomials.size();i++){
			monomials[i]*=monomial;
		}
	}
}
void Polynomial::mul_assign(const int I){
	if(I==0)
		clear();
	for(unsigned i=0;i<monomials.size();i++)
		monomials[i].coefficient*=I;
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
	for(i=0,j=0;i<monomials.size()&&j<polynomial.monomials.size();){
		if(monomials[i]<polynomial.monomials[j])
			result.monomials.push_back(monomials[i++]);
		else if(polynomial.monomials[j]<monomials[i])
			result.monomials.push_back(polynomial.monomials[j++]);
		else{
			int coeffTemp = monomials[i].coefficient+polynomial.monomials[j].coefficient;
			Monomial monoTemp(monomials[i]);
			monoTemp.coefficient=coeffTemp;
			i++,j++;
		}
	}
	if(i==monomials.size() && j!=polynomial.monomials.size()){
		for(;j<polynomial.monomials.size();j++)
			result.monomials.push_back(polynomial.monomials[j]);
	}
	if(i!=monomials.size() && j==polynomial.monomials.size()){
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
	if((monomials.size() == 0) || (polynomial.monomials.size() == 0)){
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

/*
void Polynomial::linearCoefficients(vector<Interval> & result) const{
	// initially, the result should be filled with 0

	list<Monomial>::const_iterator iter;

	for(iter = monomials.begin(); iter != monomials.end(); ++iter)
	{
		int i;

		if(iter->d > 1)
			break;

		if(iter->isLinear(i))
		{
			result[i] = iter->coefficient;
		}
	}
	
}

void Polynomial::linearCoefficients(RowVector & result) const
{
	// initially, the result should be filled with 0

	list<Monomial>::const_iterator iter;

	for(iter = monomials.begin(); iter != monomials.end(); ++iter)
	{
		int i;

		if(iter->d > 1)
			break;

		if(iter->isLinear(i))
		{
			result.set(iter->coefficient.sup(), i);
		}
	}
}

void Polynomial::constraintCoefficients(RowVector & result) const
{
	// initially, the result should be filled with 0

	list<Monomial>::const_iterator iter;

	for(iter = monomials.begin(); iter != monomials.end(); ++iter)
	{
		int i;

		if(iter->d > 1)
			break;

		if(iter->isLinear(i))
		{
			if(i > 0)
			{
				result.set(iter->coefficient.sup(), i-1);
			}
		}
	}
}

void Polynomial::constraintCoefficients(vector<Interval> & result) const
{
	// initially, the result should be filled with 0

	list<Monomial>::const_iterator iter;

	for(iter = monomials.begin(); iter != monomials.end(); ++iter)
	{
		int i;

		if(iter->d > 1)
			break;

		if(iter->isLinear(i))
		{
			if(i > 0)
			{
				result[i-1] = iter->coefficient;
			}
		}
	}
}


void Polynomial::rmConstant(){
	if(monomials.size() > 0 && (monomials.begin())->d == 0){
		monomials.erase( monomials.begin() );
	}
}
*/
int Polynomial::degree() const{
	if(monomials.size() > 0){
		return monomials.back().d;
	}
	else
	{
		return 0;
	}
}

bool Polynomial::isZero() const{
	if(monomials.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Polynomial Polynomial::derivative( const int varIndex) const{
	result = *this;

	vector<Monomial>::iterator iter;
	
	for(iter = result.monomials.begin(); iter != result.monomials.end(); ){
		if(iter->degrees[varIndex] > 0){
			double tmp = iter->degrees[varIndex];
			iter->degrees[varIndex] -= 1;
			iter->d -= 1;
			iter->coefficient *=tmp;
			++iter;
		}
		else{
			iter = result.monomials.erase(iter);
		}
	}
	return result;
}


/*
void Polynomial::sub(Polynomial & result, const Polynomial & P, const int order) const
{
	list<Monomial> monomials1, monomials2;
	list<Monomial>::const_iterator iter;

	for(iter = monomials.begin(); iter != monomials.end(); ++iter)
	{
		if(iter->d == order)
		{
			monomials1.push_back(*iter);
		}
	}

	for(iter = P.monomials.begin(); iter != P.monomials.end(); ++iter)
	{
		if(iter->d == order)
		{
			monomials2.push_back(*iter);
		}
	}

	Polynomial P1(monomials1), P2(monomials2);
	result = P1 - P2;
}
*/

string Polynomial::toString() {
	string strPoly;
	if(monomials.size() == 0){
		return "(0)";
	}
	strPoly += '(';
	for(unsigned i=0;i<monomials.size();i++){
		strPoly +=monomials[i].toString();
		if(i!=monomials.size()-1)
		  strPoly+=" + ";
	}
	strPoly += ')';
	return strPoly;
}
int Polynomial::constant(){
	if(monomials.size()>0 && monomials[0].d==0)
		return monomials[0].coefficient;
	return 0;
}
z3::expr Polynomial::intEval(const z3::expr_vector& domain)const{
	assert(domain.size()!=0);
	context& c=domain[0].ctx();
	z3::expr exp(c);
	for(unsigned i=0;i<monomials.size();i++){
		if(i==0)
		  exp=monomials[i].intEval(domain);
		else
		  exp+=monomials[i].intEval(domain);
	}
	return exp;
}

bool Polynomial::isConstant(){
	if(monomials.back().d==0)
		return true;
	return false;
}
