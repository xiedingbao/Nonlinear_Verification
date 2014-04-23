%{
  #include <stdlib.h>
  #include "Automaton.h"
  #include "parser.tab.h"
  extern void yyerror(const char *);
  extern int yylex();
  char* outchar;
  char* mychars;
  unsigned line_number=1;

%}
%option nounput 
%option noyywrap
%option noinput
%%
"automaton" 	{return AUTOMATON;}
"var" 		{return VAR;}
"synclabs" 	{return SYNCLABS;}
"initially" 	{return INITIALLY;}
"loc" 		{return LOC;}
"while" 	{return WHILE;}
"wait"  	{return WAIT;}
"when" 		{return WHEN;}
"do"   	{return DO;}
"sync" 		{return SYNC;}
"events" 	{return EVENTS;}
"goto" 		{return GOTO;}
"end"   	{return END;}
"forbidden" 	{return FORBIDDEN;}
"true" 		{return TRUE;}
"TRUE" 		{return TRUE;}
"false" 	{return FALSE;}
"FALSE" 	{return FALSE;}

"=" 		{return OEQ2;}
"==" 		{return OEQ;}
">=" 		{return OGE;}
"<=" 		{return OLE;}
">" 		{return OGT;}
"<" 		{return OLT;}
"'"  		{return PRIM;}
":=" 		{return ASSIGN;}
"^" 		{return '^';}
  
([0-9]+)(("."[0-9]+)?)((([eE])([+-]?)([0-9]+))?)  {yylval.mystring = strdup(yytext); return NUM;}
    
[-+<>*/&|(){}:;,.=!]|"["|"]" {return *yytext;}

(["$""?"a-zA-Z]|[_])("$"|"?"|[a-zA-Z]|[0-9]|[_]|[~])* {yylval.mystring = strdup(yytext); return IDENT; }


  /* rules for comments */
  
"/*"([^*]|("*"+[^*/]))*"*"+"/" /* skip comment */
"//".*                         /* skip comment XS*/
"--".*                         /* skip comment */
[\n] { ++line_number; }
[ \t\r]                      

. { //outchar=strcat("invalid character",strdup(yytext));
    outchar=strdup(yytext);
    yyerror(outchar);}
%%


