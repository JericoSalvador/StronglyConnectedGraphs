// Jerico Factor
// PA 3 
// ID: 1674120

// Digraph.c

#include <stdio.h>
#include <stdlib.h>
#include "Digraph.h"

typedef struct DigraphObj
{
	int * visitStatus; 
	List * outEdge; 
	List * inEdge; 
	int * distance; 
	int * parent; 
	int order; 
	int size; 

} DigraphObj; 

Digraph newDigraph(int numVertices)
{
	Digraph G = malloc(sizeof(DigraphObj)); 
	G->visitStatus = calloc(sizeof(int),(numVertices + 1)); 
	G->distance = calloc(sizeof(int), (numVertices + 1)); 
	G->outEdge = calloc(sizeof(List), (numVertices + 1)); 
	G->inEdge = malloc(sizeof(List) * (numVertices + 1)); 

	for(int i = 1; i <= numVertices; i++)
	{
		G->outEdge[i] = newList();
		G->inEdge[i] = newList(); 
	}
	G->order = numVertices;
	G->size = 0; 
	return G;
}

void freeDigraph(Digraph * pG)
{
	if (pG == NULL)
		return; 

	Digraph G = *pG; 
	List *ptrL; 

	for(int i = 1; i <= G->order; i++)
	{
		ptrL = G->outEdge + i; 
		freeList(ptrL); 
		ptrL = G->inEdge + i; 
		freeList(ptrL); 
	}
	free(G->distance); 
	free(G->visitStatus); 
	free(G->outEdge); 
	free(G->inEdge); 
	free(G); 
	pG = NULL; 
}

int getOrder(Digraph G)
{
	return G->order; 
}

int getSize(Digraph G)
{
	return G->size; 
}

int getOutDegree(Digraph G, int u)
{
	if (u <= 0 || u > getOrder(G))
		return -1; 

	return length(G->outEdge[u]); 

}

List getNeighbors(Digraph G, int u)
{
	if (u <= 0 || u > getOrder(G))
	{
		return NULL; 
	}
	return G->outEdge[u]; 
}

int addEdge(Digraph G, int u, int v)
{
	if (u == v)
		return 1; 

	else if (u < 1 || u > getOrder(G) || v > getOrder(G) || v < 1)
		return -1; 

	else if (inList(G->outEdge[u], v))
		return 1; 

	List uEdges = G->outEdge[u]; 
	insertSorted(uEdges, v); 
	G-> size ++; 
	return 0; 
}

int deleteNum(List L, int i)
{
	//assuming the List has no repeated value
	// returns 1 if in list and deleted
	// returns 0 if not in list; 
	Node N = getFront(L); 
	while (N != NULL)
	{
		if (getValue(N) == i)
		{
			detachNode(L, N); 
			deleteNode(N); 
			return 1; 
		}
		N = getNextNode(N); 
	}
	return 0; 
}

int deleteEdge(Digraph G, int u, int v)
{
	if (u == v)
		return -1; 

	if (u < 1 || u > getOrder(G) || v > getOrder(G) || v < 1)
		return -1; 

	if(deleteNum(G->outEdge[u], v))
		{
			G->size--; 
			return 0; 
		} 
	else 
		return 1; 
}

void printDigraph(FILE * out, Digraph G)
{
	fprintf(out, "%d", getOrder(G)); 

	List L; 
	for(int i = 1; i <= getOrder(G); i++)
	{
		L = G->outEdge[i]; 
		Node N = getFront(L);
		// printf("%d: ",i); 
		// printList(stdout, L); printf("\n");  
		while(N != NULL)
		{
			fprintf(out, ", %d %d", i, getValue(N)); 
			N = getNextNode(N); 
		}

	}

}

void unvisitAll(Digraph G)
{
	for(int i = 1; i <= getOrder(G); i ++)
	{
		G->visitStatus[i] = UNVISITED; 
	}
}

int getMark(Digraph G, int u)
{
	return G->visitStatus[u]; 
}

void setMark(Digraph G, int u, int theMark)
{
	if (theMark == UNVISITED || theMark == INPROGRESS || theMark == ALLDONE)
		G->visitStatus[u] = theMark; 

	else
	{
		printf("Error: invalid Mark\n"); 
		exit(1);
	}
}



// For clarity 
void enqueue(List L, int i)
{
	append(L,i); 
}
int dequeue(List L)
{
	int num = getValue(getFront(L)); 
	deleteFront(L); 
	return num; 
}
void push(List L, int i)
{
	prepend(L, i); 
}
int pop(List L)
{
	int num = getValue(getFront(L)); 
	deleteFront(L); 
	return num; 
}

void distance(FILE* out, Digraph G, int u, int v)
{
	if(u == v)
	{
		fprintf(out, "%d\n", 0);
		return;  
	}

	unvisitAll(G); 
	int cur; 
	List neighbors; 
	List Q = newList(); 
	enqueue(Q, u);
	G->distance[u] = 0; 
	while(length(Q) != 0)
	{
		cur = dequeue(Q); 
		setMark(G,cur,INPROGRESS); 
		neighbors = G->outEdge[cur]; 
		Node N = getFront(neighbors); 
		while(N != NULL)
		{
			if(getMark(G,getValue(N)) == UNVISITED)
			{
				setMark(G, getValue(N), INPROGRESS);
				G->distance[getValue(N)] = G->distance[cur] + 1; 
				if(getValue(N) == v)
				{
					fprintf(out, "%d\n", G->distance[v]);
					freeList(&Q); 
					return;  
				}
				enqueue(Q, getValue(N));  
			}
			N = getNextNode(N); 
		}
		setMark(G, cur, ALLDONE); 
	}
	
	freeList(&Q); 
	fprintf(out, "INF\n"); 
	
}

int acyclic_recursive(Digraph G, int u)
{
	if(getMark(G,u) == INPROGRESS)
	{
		return 0; 
	}
	setMark(G, u, INPROGRESS); 
	Node N = getFront(G->outEdge[u]); 
	int returnValue = 1; 
	while(N != NULL)
	{
		if (acyclic_recursive(G,getValue(N))==0)
			returnValue = 0; 
		N = getNextNode(N); 
	}

	setMark(G, u, ALLDONE); 
	return returnValue; 
}

void acyclic(FILE* out, Digraph G)
{
	unvisitAll(G); 

	for(int i = 1; i <= getOrder(G); i ++)
	{
		if(G->visitStatus[i] == UNVISITED)
		{
			int j = acyclic_recursive(G,i); 
			if( j == 0)
			{
				fprintf(out, "NO\n"); 
				return; 
			}

		}
	}
	fprintf(out, "YES\n");
}

void topoSort_recursive(Digraph G, int u, List stack)
{
	setMark(G, u, INPROGRESS); 
	Node N = getFront(G->outEdge[u]); 
	while(N != NULL)
	{
		if(getMark(G, getValue(N)) == UNVISITED)
			topoSort_recursive(G, getValue(N), stack); 
		N = getNextNode(N); 
	}
	push(stack, u); 
	setMark(G,u,ALLDONE); 
}

void topoSort(FILE* out, Digraph G)
{
	// Check acyclic 
	unvisitAll(G); 
	for(int i = 1; i <= getOrder(G); i ++)
	{
		if(G->visitStatus[i] == UNVISITED)
		{
			int j = acyclic_recursive(G,i); 
			if( j == 0)
			{
				fprintf(out, "IMPOSSIBLE\n"); 
				return; 
			}
		}
	}

	List stack = newList(); 

	unvisitAll(G); 

	for(int i = 1; i <= getOrder(G); i++)
	{
		if(G->visitStatus[i] == UNVISITED)
		{
			topoSort_recursive(G, i, stack); 
		}
		
	}
	// printList(out, topoSortedStack); fprintf(out, "\n");  
	printList(out, stack); fprintf(out, "\n");  
	freeList(&stack); 
}
















