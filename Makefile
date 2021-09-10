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

all: tc0001

tc0001: Node.hpp BST.hpp tc0001.cpp

clean:;	rm -fr core *.o tc???? tc????.exe
