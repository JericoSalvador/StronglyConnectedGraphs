#------------------------------------------------------------------------------
# Makefile for CMPS 101-01 Programming Assignment 2
#
#       make                   makes DigraphProperties
#       
#------------------------------------------------------------------------------

DigraphProperties: Digraph.o DigraphProperties.c List.o
	gcc -Wall -o DigraphProperties DigraphProperties.c List.o Digraph.o 

test: Digraph.o List.o test.c
	gcc -Wall -o test test.c List.o Digraph.o

Digraph.o: Digraph.h Digraph.c
	gcc -c -std=c99 -Wall Digraph.c 

List.o: List.c List.h
	gcc -c -std=c99 -Wall List.c

clean: 
	rm -f *.o DigraphProperties test