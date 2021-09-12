#
# Makefile
# ------------------------------------------------------------------------------
# Binary Search Tree
# ------------------------------------------------------------------------------
# Main Makefile
# ------------------------------------------------------------------------------
# Ver   1.00  Initial version                                       September 21
# ------------------------------------------------------------------------------
# (C) A.Yakovlev, 2021
#

CXX := g++

CXXFLAGS += -g3 -Wall -std=c++2a
LDFLAGS  +=
LDLIBS   += 

.cpp:;	${CXX} ${CXXFLAGS} ${LDFLAGS} $< -o $@ ${LDLIBS}

all: $(basename $(wildcard tc????.cpp))

tc%: tc%.cpp Node.hpp BST.hpp

clean:;	rm -fr core *.o tc???? tc????.exe
