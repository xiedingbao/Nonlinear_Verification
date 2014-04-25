#include "general.h"
using namespace std;


void throw_error(const char*  s){
	cout << "fatal error: " << s << endl << flush;
	exit(1);
}

void throw_error(string msg){
	throw_error(msg.c_str());
}

void message(int level,string content){
	if(VERBOSE_LEVEL>=level)
	  std::cout<<content<<std::endl;
}

// convert integer to char, but only up to 256 digits!
string int2string(const int i)
{
  char chr[256];
  string str;
  sprintf(chr,"%i",i);
  str=chr;
  return str;
}

string unsigned2string(unsigned i){
	char ch[256];
	sprintf(ch,"%d",i);
	return string(ch);
}

 // convert integer to char, but only up to 256 digits!
string double2string(const double d)
{
  char chr[256];
  string str;
  sprintf(chr,"%g",d);
  str=chr;
  return str;
}


