SHELL = /bin/bash


# Build Objects
SRCS		= $(wildcard *.cpp)
OBJS		= $(SRCS:%.cpp=%.o)


# Compiler
CXX 		= g++
CPPFLAGS	=
CXXFLAGS 	=
LIBFLAGS 	=

.PHONY: clean all 

all: $(OBJS) $(OBJ_DIR)

# Targets
$(OBJS): %.o : %.cpp 
	$(CXX) $(CXXFLAGS) -c $< -o $@ 

all: $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o main

clean:
	rm -rf *.o
