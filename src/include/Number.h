#ifndef _BACH_NUMBER_H
#define _BACH_NUMBER_H
#include <mpfr.h>
#include <string>
#include "z3++.h"

class Number{
private:
	mpfr_t value;
public:
	Number();
	Number(const char* str);
	Number(const Number& num);
	~Number();

	bool operator == (const Number& num) const;
	bool operator != (const Number& num) const;

	
	Number & operator = (const Number& num);
	Number & operator += (const Number& num);
	Number & operator -= (const Number& num);
	Number & operator *= (const Number& num);
	Number & operator ++ ();
	Number & operator -- ();

	const Number operator + (const Number& num) const;
	const Number operator - (const Number& num) const;
	const Number operator * (const Number& num) const;
	const Number operator / (const Number& num) const;

	void inv(Number & result) const;
	void inv_assign();
	std::string toString()const;
	z3::expr z3_val(z3::context & c) const;

};



#endif
