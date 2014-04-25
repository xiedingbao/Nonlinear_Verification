#ifndef _MONOMIAL_H
#define _MONOMIAL_H
#include <string>
#include <stdio.h>
#include <cassert>
#include <vector>
#include "z3++.h"
#include "general.h"
#include "Number.h"


class Monomial{
private:
	Number coefficient;		    // the coefficient of the monomial
	std::vector<int> degrees;	// the degrees of the variables, e.g., [2,0,4] is the notation for x1^2 x3^4
	int d;			            // the degree of the monomial, it is the sum of the values in degrees.

public:
	Monomial();								// empty monomial.
	Monomial(Number I, const std::vector<int> & degs);
	Monomial(const Monomial & monomial);
	Monomial(const Number & I, const int numVars);			// a constant
	~Monomial();
	int degree() const;											// degree of the monomial
	unsigned dimension() const;										// dimension of the monomial
	z3::expr intEval(const z3::expr_vector& domain) const;
	Monomial & operator  = (const Monomial & monomial);
	Monomial & operator += (const Monomial & monomial);			// we assume the two monomials can be added up
	Monomial & operator *= (const Monomial & monomial);
	const Monomial operator + (const Monomial & monomial) const;
	const Monomial operator * (const Monomial & monomial) const;
	bool isLinear(int & index) const;					  // Check if the degree of the monomial is 1. If so then return the index of the variable of degree 1.
	std::string toString();
	
	friend bool operator < (const Monomial & a, const Monomial & b);	// Define a partial order over the monomials
	friend bool operator == (const Monomial & a, const Monomial & b);
	friend class Polynomial;
};



#endif
