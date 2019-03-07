// Jerico Factor
// PA 3
// ID: 1674120

// Digraph.h

#ifndef DIGRAPH_H
#define DIGRAPH_H

#define UNVISITED 0
#define INPROGRESS 1
#define ALLDONE -1

#define FOUND 505
#define NOTFOUND 404

#include "List.h"

typedef struct DigraphObj * Digraph; 


Digraph newDigraph(int numVertices);
// Returns a Digraph that points to a newly created DigraphObj representing a digraph which has
// n vertices and no edges.

void freeDigraph(Digraph* pG);
// Frees all dynamic memory associated with its Digraph* argument, and sets
// *pG to NULL.

int getOrder(Digraph G);
// Returns the order of G, the number of vertices in G.

int getSize(Digraph G);
// Returns the size of G, the number of edges in G.

int getOutDegree(Digraph G, int u);
// Returns the number of outgoing neighbors that vertex u has in G, the number of vertices v such
// that (u, v) is an edge in G. Returns -1 if v is not a legal vertex.

List getNeighbors(Digraph G, int u);
List getInNeighbors(Digraph G, int u); 
// Returns a list that has all the vertices that are outgoing neighbors of vertex u, i.e.,
// a list that has all the vertices v such that (u, v) is an edge in G.
// There is no input operation that corresponds to getNeighbors

int addEdge(Digraph G, int u, int v);
// Adds v to the adjacency list of u, if that edge doesn’t already exist.
// If the edge does already exist, does nothing. Used when edges are entered or added.
// Returns 0 if (u, v) is a legal edge, and the edge didn’t already exist.
// Returns 1 if (u, v) is a legal edge and the edge did already exist.
// Returns -1 if (u, v) is not a legal edge.

int deleteEdge(Digraph G, int u, int v);
// Deletes v from the adjacency list of u, if that edge exists.
// If the edge doesn’t exist, does nothing. Used when edges are deleted.
// Returns 0 if (u, v) is a legal edge, and the edge did already exist.
// Returns 1 if (u, v) is a legal edge and the edge didn’t already exist.
// Returns -1 if (u, v) is not a legal edge.

int getCountSCC(Digraph G);
// Returns the number of Strongly Connected Components in G.

int getNumSCCVertices(Digraph G, int u);
// Returns the number of vertices (including u) that are in the same Strongly Connected Component
// as u in G.. Returns -1 if u is not a legal vertex.

int inSameSCC (Digraph G, int u, int v);
// Returns 1 if u and v are in the same Strongly Connected Component of G, and returns 0 if u and v
// are not in the same Strongly Connected Component of the current digraph.
// A vertex is always in the same Strongly Connected Component as itself.
// Returns -1 if u is not a legal vertex.

void unvisitAll(Digraph G);

int getMark(Digraph G, int u);

void setMark(Digraph G, int u, int theMark);

void printDigraph(FILE* out, Digraph G);
// Outputs the digraph G in the same format as an input line, including the number of vertices
// and the edges. The edges should be in sorted order, as described above.

void distance(FILE* out, Digraph G, int u, int v);
// Outputs the distance between vertices u and v if there is a directed path between them in the
// digraph. Otherwise, outputs INF

void acyclic(FILE* out, Digraph G);
// Outputs YES if the digraph is acyclic. Otherwise, outputs NO.

void topoSort(FILE* out, Digraph G);
// Outputs a topological sort of the digraph. If the digraph is not acyclic, outputs IMPOSSIBLE.

#endif //DIGRAPH_H