
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
	Digraph G = newDigraph(6); 

	addEdge(G,1,6);
	fprintf(stdout,"1 worked\n"); 
	addEdge(G,4,1); 
	fprintf(stdout,"2 worked\n"); 
	//addEdge(G,4,3); 
	fprintf(stdout,"3 worked\n"); 
	addEdge(G,5,4);
	fprintf(stdout,"4 worked\n"); 
	addEdge(G,5,3);
	fprintf(stdout,"3 worked\n"); 
	addEdge(G,5,2);
	addEdge(G,6,5); 
	addEdge(G,6,4);
	addEdge(G,2,3);
	addEdge(G,3,2);  

	printDigraph(stdout, G); fprintf(stdout, "\n"); 
	printf("%d\n", getCountSCC(G)); 
	printf("%d\n", getNumSCCVertices(G,4)); 
	printf("%d\n", inSameSCC(G,2,1)); 
	freeDigraph(&G); 
	// func(fun); 
	
}