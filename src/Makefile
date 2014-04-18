CXX=g++
CFLAGS=-o2 -Wall -Iinclude
LDFLAGS=-lpthread -lz3
CPPFILES = $(shell find -name "*.cpp")
OBJS = $(CPPFILES:.cpp=.o)
all:main
	@echo "Congratulations"
	
main: $(OBJS)
		$(CXX)  $(OBJS) -o bach $(LDFLAGS)
	
%.o:%.cpp
	$(CXX) -c $(CFLAGS) -o $@ $<

.PHONY: clean
clean:
	rm -f *.o *.~ main
