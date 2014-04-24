#include <stdio.h>
#include <iostream>
#include <map>
#include <string>
#include<stdlib.h>


extern int VERBOSE_LEVEL;


void pause_key();
 
void throw_error(std::string s);

void throw_warning(std::string s);

void message(unsigned int level, std::string s);

std::string int2string(const int i);
std::string unsigned2string(const unsigned i);
std::string double2string(const double d);

				
