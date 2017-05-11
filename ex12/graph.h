#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#define __USE_BSD // make prototype for strdup visible
#include <string.h>
// #define BFS
// #undef DFS

typedef struct linkedlist { // linked list of ints (for use in Node)
  int index;
  struct linkedlist *next;
} List;

typedef struct { // a Node of a Graph
  char *name;
  List *outlist; // adjacency list
  int outdegree; // length of outlist
  //double pagerank_score; //not needed for this exercise
} Node;

typedef struct {
  // your code goes here
	Node *table;
	int MaxSize;

} Graph;

// use to check result of strdup, malloc etc.
extern void check (void *memory, char *message);

extern int initialize_graph (Graph *mygraph, int MaxSize);
extern int insert_graph_node (Graph *mygraph, int n, char *name);
extern int insert_graph_link (Graph *mygraph, int source, int target);
extern int read_graph (Graph *mygraph, char *filename);
extern void print_graph (Graph *mygraph);
extern int *dijkastraShortestPaths(Graph* mygraph, int v);
extern void heapInsert(int *distance, int *Q, int index);
extern int heapRemoveMin(int *Q, int *distance);



extern void BFS (Graph *mygraph, int sNode, int lNode);
extern void DFS (Graph *mygraph, int sNode, int lNode);
// #ifdef BFS
// extern void BFS (Graph *mygraph, int sNode, int lNode);
// #endif
// #ifdef DFS
// extern void DFS (Graph *mygraph, int sNode, int lNode);
// #endif