/* Bounded reachability analysis of polynomial hybrid automata based on 
 * the quantifier-free encoding proposed by cimatti in FMCAD2012
 * Author: Dingbao Xie
 * Email: xiedingbao@gmail.com
 * 2014/04/19 (start)
 * */
#ifndef _NONLINEAR_BACH_H
#define _NONLINEAR_BACH_H
#include <stdio.h>
#include <stdlib.h>
#include <cassert>
#include "System.h"
#include "Automaton.h"
#include "parser.tab.h"

extern FILE *yyin;
int VERBOSE_LEVEL = 0;
int inputbound=0;


void welcome_message();
void help_message();
void info_message();
void process_flag(const char *flagstr);
void process_flags(int agc, char *agv[]);


static bool match(const char *& in, const char *str){
	int i;
	for (i=0; str[i] != '\0'; i++)
	  if (in[i] != str[i])
		return false;
	in +=i;
	return true;
}

#endif

