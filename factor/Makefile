# Makefile: Makefile for factor project.
# 
# Author:      Joshua Morrison (GitHub: MrM21632)
# Last Edited: 7/7/2018, 10:00pm

CXX ?= g++
OBJECTS = prime_utils.o factor_utils.o factor.o
HEADERS = factor_utils.h prime_utils.h
# Change the extension if you want.
EXE = factor

default: $(EXE)

prime_utils.o: prime_utils.cpp prime_utils.h
	$(CXX) -c prime_utils.cpp
factor_utils.o: factor_utils.cpp $(HEADERS)
	$(CXX) -c factor_utils.cpp
factor.o: factor.cpp $(HEADERS)
	$(CXX) -c factor.cpp

# Change the names of the Boost library files if they aren't the same
# on your system as they are below.
$(EXE): $(OBJECTS)
	$(CXX) -o $(EXE) $(OBJECTS) -lboost_random -lboost_system

clean:
	rm -rf *.o $(EXE)
