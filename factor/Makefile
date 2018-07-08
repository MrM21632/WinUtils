# Makefile: Makefile for factor project.
# 
# Author:      Joshua Morrison (GitHub: MrM21632)
# Last Edited: 7/7/2018, 10:00pm

OBJECTS = prime_utils.o factor_utils.o factor.o
HEADERS = factor_utils.h prime_utils.h

default: factor.exe

prime_utils.o: prime_utils.cpp prime_utils.h
	g++ -c prime_utils.cpp

factor_utils.o: factor_utils.cpp $(HEADERS)
	g++ -c factor_utils.cpp

factor.o: factor.cpp $(HEADERS)
	g++ -c factor.cpp

factor.exe: $(OBJECTS)
	g++ -o factor.exe $(OBJECTS)

clean:
	del *.o
	del factor.exe
