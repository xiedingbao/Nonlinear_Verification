#include "Number.h"

mpfr_prec_t prec=255;

Number::Number(){
	mpfr_init2(value, prec);
	mpfr_set_str(value, "0", 10, GMP_RNDN);
}

Number::Number(const char* str){
	mpfr_init2(value, prec);
	mpfr_set_str(value, str, 10, GMP_RNDN);
}

Number::Number(const Number & num){
	mpfr_init2(value, prec);
	mpfr_set(value, num.value, GMP_RNDN);
}

Number::~Number(){
	mpfr_clear(value);
}

bool Number::operator == (const Number & num) const{
	return (mpfr_cmp(value,num.value)==0);
}

bool Number::operator != (const Number & num) const{
	return (mpfr_cmp(value,num.value)!=0);
}


Number & Number::operator = (const Number & num){
	if(this == &num)
		return *this;
	mpfr_set(value, num.value, GMP_RNDN);
	return *this;
}
Number & Number::operator += (const Number & num){
	mpfr_add(value, value, num.value, GMP_RNDN);
	return *this;
}
Number & Number::operator -= (const Number & num){
	mpfr_sub(value, value, num.value, GMP_RNDN);
	return *this;
}
Number & Number::operator *= (const Number & num){
	mpfr_mul(value, value, num.value, GMP_RNDN);
	return *this;
}


Number & Number::operator ++ (){
	Number tmp("1");
	*this+=tmp;
	return *this;
}

Number & Number::operator -- (){
	Number tmp("1");
	*this-=tmp;
	return *this;
}
const Number Number::operator + (const Number & num) const{
	Number result = *this;
	result += num;
	return result;
}

const Number Number::operator - (const Number & num) const{
	Number result = *this;
	result -= num;
	return result;
}

const Number Number::operator * (const Number & num) const{
	Number result = *this;
	result *= num;
	return result;

}

const Number Number::operator / (const Number & num) const{

	return *this;
}

void Number::inv(Number & result) const{
	Number n("-1");
	result = *this * n;
}

void Number::inv_assign(){
	Number result;
	this->inv(result);
	*this = result;
}

z3::expr Number::z3_val(z3::context & c)const{
	char ch[256];
	mpfr_sprintf(ch, "%.16Rf", value);
	return c.real_val(ch);
}

std::string Number::toString() const{
	char ch[256];
	mpfr_sprintf(ch, "%.4Rf", value);
	return std::string(ch);
}

