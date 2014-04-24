#ifndef _POLYNOMIAL_H
#define _POLYNOMIAL_H
#include "Monomial.h"
#include <vector>

class Polynomial{				// polynomials in monomial form
private:
	std::vector<Monomial> monomials;
//	std::vector<std::string> varNames;
public:
	Polynomial();														// empty polynomial
	Polynomial(const int constant, const int numVars);			// constant polynomial where dim is the number of the variables
	Polynomial(const Monomial & monomial);		// polynomial with one monomial
	Polynomial(const std::vector<Monomial> & monos);
	Polynomial(const Polynomial & polynomial);
	~Polynomial();

	void reorder();														// sort the monomials.
	void clear();


	int constant() ;											// constant part of the polynomial
	void inv(Polynomial & result) const;											// additive inverse
	void inv_assign();
//	void add_assign(const Monomial & monomial);										// add a monomial
//	void sub_assign(const Monomial & monomial);										// subtract a monomial
	void mul_assign(const Monomial & monomial);										// multiplied by a monomial

	void mul_assign(const int I);											// multiplied by an interval
//	void div_assign(const Interval & I);											// divided by an interval
//	void mul(Polynomial & result, const Interval & I) const;
//	void div(Polynomial & result, const Interval & I) const;

//	void mul_assign(const int varIndex, const int degree);							// multiplied by a term x^d
//	void mul(Polynomial result, const int varIndex, const int degree) const;

	Polynomial & operator = (const Polynomial & P);
	Polynomial & operator += (const Polynomial & polynomial);
	Polynomial & operator -= (const Polynomial & polynomial);
	Polynomial & operator *= (const Polynomial & polynomial);
	const Polynomial operator + (const Polynomial & polynomial) const;
	const Polynomial operator - (const Polynomial & polynomial) const;
	const Polynomial operator * (const Polynomial & polynomial) const;

	z3::expr intEval(const z3::expr_vector& domain) const;
//	void rmConstant();				// remove the constant part
	int degree() const;				// degree of the polynomial
	bool isZero() const;

	Polynomial derivative(const int varIndex) const;					// derivative with respect to a variable
//	void sub(Polynomial & result, const Polynomial & P, const int order) const;		// compute the subtraction of the monomials with some order
	bool isConstant();	
	std::string toString();	// transform a polynomial to a string

	friend class Verification;
};

#endif
