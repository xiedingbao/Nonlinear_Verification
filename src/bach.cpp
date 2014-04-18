#include "bach.h"

bool statistic = false;

int main(int argc, char *argv[]){
	// terminate if only display options, no arguments, i.e. no filename
	if (argc == 1) {
		help_message();
    	exit(1);
	}
	process_flags(argc,argv);
	if(statistic){
		double mem_used_peak = memUsedPeak();
		double cpu_time = cpuTime();
		if (mem_used_peak != 0) 
			printf("Memory used: %.2f MB\n", mem_used_peak);
		printf("CPU Time: %g s\n", cpu_time);
	}
	return 0;
}


void welcome_message(){
	printf( "BACH_Nonlinear, last modified April, 2014\n ");
}

void help_message(){
	printf("Usage: bach [OPTIONS] <filename> <bound>\n\n");      
	printf("Command line options:\n");   
	printf(" -help show help information\n\n");   
	printf("For further information, please visit: http://seg.nju.edu.cn/BACH/\n");
	printf("or contact xiedingbao@gmail.com\n" );
}

void info_message(){
	printf("The following options are available\n");
	printf(" -verbose=INT detailed out (0:silent, 1:some, 2:all, 3:debug)\n");
	printf(" -st show the statistical information (spent time and peak memory usage)\n");
	printf(" -help show help information:\n\n");
}



/* process the command options */
void process_flag(const char* flagstr){
	if(match(flagstr, "help")){
		welcome_message();
		info_message();
		exit(1);
	}
	else if (match(flagstr, "st")){
		statistic=true;
	}
	else if (match(flagstr, "verbose")){
		if(flagstr[0]=='='){
			VERBOSE_LEVEL = atoi(flagstr+1);
			printf("Setting output level to %d\n",VERBOSE_LEVEL);
		}
		else
			printf("Please input -verbose=<INT>\n");

	}
	else
		printf("Warning: illegal flag (%s) ignored\n", flagstr);
}

void process_flags(int agc, char *agv[]) {
	char* infilename=NULL;
 	for(int i=1; i<agc; i++) {
		if (agv[i][0] == '-') {
			// then process a flag
			process_flag(agv[i]+1);
		}
		else {
			// parse as input file
			if(infilename == NULL){
				infilename = agv[i];
			}
			else{
				inputbound=atoi(agv[i]);
				if(inputbound <= 0){
					fprintf(stderr,"The bound should be a positive integer!");
					exit(1);
				}
			}
		}
    }
/*	if(parameter>=1){
		printf("Parsing file %s .\n",infilename);
		yyin = fopen(infilename, "r" );	//doesn't deal with recursive loads 
		if (yyin == NULL){
			fprintf(stderr, "*** Error opening `%s' ***\n", infilename);
			fflush(stderr);
			exit(1);
		}
        else{
          	yyparse();
		fclose(yyin);	
		}
	}
	else
		help_message();
*/
}


