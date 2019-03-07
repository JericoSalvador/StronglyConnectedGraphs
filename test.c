
#include <stdio.h>
#include <stdlib.h>
#include "Digraph.h"

int fun(int x)
{
	return x + 5; 
}

void func(int (*f)(int))
{
	printf("%d\n", f(2)); 
}

int main(void)
{
	Digraph G = newDigraph(4); 

	for(int i = 4; i > 1; i--)
	{
		addEdge(G, i, i-1); 
	}
	addEdge(G,1,2); 
	// addEdge(G, 1,4); 
	// printList(stdout, getInNeighbors(G, 2)); printf("\n"); 
	// deleteEdge(G, 1,2); 
	// printList(stdout, getInNeighbors(G, 2)); printf("\n"); 
	// printf("%d\n", 0x7FFFFFFF); 
	printf("%d\n", getCountSCC(G)); 
	printf("%d\n", getNumSCCVertices(G,4)); 
	printf("%d\n", inSameSCC(G,2,1)); 
	freeDigraph(&G); 
	// func(fun); 
	
}