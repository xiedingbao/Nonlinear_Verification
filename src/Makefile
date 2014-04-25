CXX=g++
CFLAGS=-o2 -g -Wall -Iinclude -I. -D __STDC_LIMIT_MACROS -D __STDC_FORMAT_MACROS 
LDFLAGS=-lpthread -lz3 -lminisat -lmpfr  
CPPFILES = $(shell find -name "*.cpp")
OBJS = $(CPPFILES:.cpp=.o)

all:bach
	@echo "Congratulations"
	
bach: lex.yy.o parser.tab.o $(OBJS) 
		$(CXX)  -o $@ $^ $(LDFLAGS)
	
%.o:%.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<
%.o:%.c
	$(CXX) -c $(CFLAGS) -o $@ $<

parser.tab.c parser.tan.h:parser.y
	bison -d parser.y

lex.yy.c:parser.l parser.tab.c
	flex parser.l

.PHONY: clean
clean:
	rm -f *.o *~ include/*~  bach parser.tab.c parser.tab.h
