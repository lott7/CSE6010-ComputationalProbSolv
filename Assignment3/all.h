#ifndef ALL_H
#define ALL_H
#include <stdio.h>
#include <stdlib.h>

// Typedef and function definitions for the graph representation using adjacency list
typedef struct edge {
    int to_vertex; // specifies to which vertex the edge is connected to
    int edge_label; // either 1 (frequent contacts) or 2 (occasional contacts)
    struct edge *next; // one vertex might have more than one edge to another vertex
} Edge;

typedef struct vertex {
    int visited; // either 0 (not visited) or 1 (visited);
    Edge *edges;
} Vertex;

typedef struct graph {
    int num_vertices; // total number of vertices the graph contains
    Vertex *vertices;
} Graph;

int readGraphFile(const char *filename, int edgeLabel, Graph *graph);
void InitializeNewEdge(Graph *graph, int from, int to, int label);
void printAdjacencyList(const Graph *graph);
void freeGraphMemory(Graph *graph);


// Typedef and function definitions for depth first search algorithm using a stack (array implementation)
typedef struct stack {
    int top;
    int* array;
} Stack;

void push(Stack* stack, int item);
int pop(Stack* stack);
int isEmpty(Stack* stack);
void depthFirstSearch(Graph *graph, int arraySize);
int countConnectedVertices(Graph *graph);

#endif
