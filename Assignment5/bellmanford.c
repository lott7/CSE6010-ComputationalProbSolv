#include "bellmanford.h"

// Commented out for DEBUG mode, uncomment to enable debugging
// #define DEBUG

// Function to read the graph from a given file and store the data into a structure
void readGraphFile(const char *file_name, Graph *graph) {
    FILE *file = fopen(file_name, "r");
    if (file == NULL) { // Error message if file cannot be opened
        printf("Error: Unable to open input file %s\n", file_name);
        return;
    }
    // Reading the first line of the file
    int num_vertices, num_edges;
    fscanf(file, "%d %d", &num_vertices, &num_edges);

    // Initialize the graph utilizing dynamic memory allocation
    graph->num_vertices = num_vertices;
    graph->num_edges = num_edges;
    graph->vertices = (Vertex *)malloc(num_vertices * sizeof(Vertex));

    // Initialize the vertices
    for (int i=0; i<graph->num_vertices; i++) { 
        graph->vertices[i].d = DBL_MAX;
        graph->vertices[i].p = -1;
        graph->vertices[i].visited = 0;
        graph->vertices[i].edges = NULL;
    }

    // Reading from the second line and labeling the three input lines respectively
    int from, to;
    double weight;
    while (fscanf(file, "%d %d %lf", &from, &to, &weight) == 3) {
        if (0 <= from && from < graph->num_vertices && 0 <= to && to < graph->num_vertices) {
            // Add an edge to the already stored vertices in the graph    
            initializeNewEdge(graph, from, to, weight);
        }
    }
    fclose(file);
}

// Function to initialize a new edge to an existing vertex
void initializeNewEdge(Graph *graph, int from, int to, double weight) {
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
 
        // Assign the values to their respective structure counterparts
        newEdge->to_vertex = to;
        newEdge->weight = weight;
        newEdge->next = graph->vertices[from].edges;

        graph->vertices[from].edges = newEdge;
}

// Bellman-Ford algorithm
void bellmanFord(Graph *graph, int num_threads, int source_vertex, int destination_vertex) {
    int flag, temp;
    int num_vertices = graph->num_vertices;

    // Initialize distance for the source node
    graph->vertices[source_vertex].d = 0;

    // Activate the flag to "true"
    flag = 1;

    // Stop the time spent in the parallel section
    double start_time, end_time;
    start_time = omp_get_wtime();

    // Parallelizing the execution of the Bellman-Ford algorithm
    // #pragma omp parallel 
    {
        while (flag) {
            flag = 0;

            // Relax edges repeatedly until no further improvement can be computed
            #pragma omp parallel for
            for (int j=0; j<num_vertices; ++j) {
                Edge *edge = graph->vertices[j].edges;
                while (edge != NULL) {
                    temp = relax(graph, &(graph->vertices[j]), edge);
                    if (temp == 1) {
                        flag = 1;
                    }
                    edge = edge->next;
                }
            }
        }
    }
    end_time = omp_get_wtime();

    // Output results based on the command-line arguments
    if (destination_vertex >= 0 && destination_vertex < num_vertices) {
        // Output results for a single destination vertex
        printPath(graph, source_vertex, destination_vertex);
    } else {
        // Output results for all vertices
        for (int i=0; i<num_vertices; ++i) {
            printPath(graph, source_vertex, i);
        }
    }
    // Print the elapsed time spent in the parallel section
    printf("%f\n", (end_time - start_time));
}

// Relaxation function
int relax(Graph *graph, Vertex *u, Edge *edge) {
    int v = edge->to_vertex;
    double weight = edge->weight;
    if (u->d + weight < graph->vertices[v].d) {
        graph->vertices[v].d = u->d + weight;
        graph->vertices[v].p = u - graph->vertices; // // Set predecessor to the index of 'u'
        graph->vertices[v].visited = 1;  // Mark the vertex as visited
        // Indicate that relaxation occurred
        return 1;
    }
    // Indicate that relaxation did not occur
    return 0;
}

// Function to print out all elements of the adjacency list to the console
void printAdjacencyList(const Graph *graph) {
    for (int i=0; i<graph->num_vertices; i++) {
        printf("Vertex %d: ", i); // print a given vertex i
        Edge *currentEdge = graph->vertices[i].edges;
        while (currentEdge != NULL) { // print all the edges belonging to the chosen vertex i
            printf("(%d, %f) ", currentEdge->to_vertex, currentEdge->weight);
            currentEdge = currentEdge->next;
        }
        printf("\n");
    }
}

// Function to print the path from the source_vertex to the destination_vertex
void printPath(const Graph *graph, int source_vertex, int destination_vertex) {
    // Print information about the shortest path from source to destination
    printf("%d: ", destination_vertex);

    if (graph->vertices[destination_vertex].d == DBL_MAX) {
        // No path exists, print INFTY
        printf("INFTY; %d\n", destination_vertex);
        return;
    }
    // Print the shortest path length with 5 decimal places
    printf("%.5f; ", graph->vertices[destination_vertex].d);

    // Print the path recursively
    printPathRecursively(graph, source_vertex, destination_vertex);
    
    // Ensure a new line is created
    printf("\n");
}

// Function to recursively print the path
void printPathRecursively(const Graph *graph, int source_vertex, int current_vertex) {
    if (current_vertex == source_vertex) {
        // Base case: reached the source vertex
        printf("%d ", source_vertex);
        return;
    }
    // Recursive case: print the path from source to current_vertex
    printPathRecursively(graph, source_vertex, graph->vertices[current_vertex].p);

    // Print the current vertex
    printf("%d ", current_vertex);
}

// Function to free the dynamically allocated memory
void freeGraphMemory(Graph *graph) {
    // Free dynamically allocated memory
    if (graph == NULL) { // adjacency list is empty; return
#ifdef DEBUG
        printf("Adjacency list is empty!\n");
#endif
        return; 
    }
    // Free the graph node by node with all edges accordingly
    for (int i=0; i<graph->num_vertices; i++) {
        Edge* current_edge = graph->vertices[i].edges;
        while (current_edge != NULL) {
            Edge* temp = current_edge;
            current_edge = current_edge->next;
            free(temp);
        }
        graph->vertices[i].edges = NULL; // Set edges pointer to NULL after freeing
    }
    free(graph->vertices); // Free memory allocated to vertices
    graph->vertices = NULL;
}
