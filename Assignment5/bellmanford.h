#ifndef BELLMANFORD_H
#define BELLMANFORD_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <omp.h>

typedef struct edge {
    int to_vertex; // Specifies to which vertex the edge is connected
    double weight; // Weight (cost) of the edge
    struct edge *next; // One vertex might have more than one edge to another vertex
} Edge;

typedef struct vertex {
    double d; // Minimum distance (weight) path from source node s0 (upper bound)
    int p; // Predecessor in the minimum weight path computed so far
    int visited;  // Tracks whether the vertex has been relaxed
    Edge *edges;
} Vertex;

typedef struct graph {
    int num_vertices; // Total number of vertices the graph contains
    int num_edges; // Total number of edges the graph contains
    Vertex *vertices;
} Graph;

void readGraphFile(const char *file_name, Graph *graph);
void initializeNewEdge(Graph *graph, int from, int to, double weight);
void bellmanFord(Graph *graph, int num_threads, int source_vertex, int destination_vertex);
int relax(Graph *graph, Vertex *u, Edge *edge);
void printAdjacencyList(const Graph *graph);
void printPath(const Graph *graph, int source_vertex, int destination_vertex);
void printPathRecursively(const Graph *graph, int source_vertex, int current_vertex);
void freeGraphMemory(Graph *graph);

#endif