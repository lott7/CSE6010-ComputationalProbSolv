#include "all.h"

#define MAXSIZE 1000
// #define DEBUG

// Function implementations for adjacency list
//
// Function to read the graph from a given file and store the data into a structure
int readGraphFile(const char *filename, int edgeLabel, Graph *graph) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) { // error message if file cannot be opened
        printf("Failed to open file %s\n", filename);
        return 1;
    }
    // Reading the first line of the file to get the nuber of vertices
    int numVertices;
    if (fscanf(file, "%d", &numVertices) != 1) {
        printf("Failed to read the number of vertices from file %s\n", filename);
        fclose(file);
        return 1; // Return an error code indicating a read error
    }
    graph->num_vertices = numVertices; // store the value into the graph structure
    graph->vertices = (Vertex *)malloc(numVertices * sizeof(Vertex));

    if (graph == NULL) { // Memory allocation failed; return failure
		printf("Memory allocation failed!\n");
        return 1; 
    }
    // Initialize the vertices
    for (int i=0; i<graph->num_vertices; i++) { 
        graph->vertices[i].edges = NULL;
        graph->vertices[i].visited = 0;
    }
    // Reading from the second line and labeling the three input lines respectively
    int from, to, label;
    while (fscanf(file, "%d %d %d", &from, &to, &label) == 3) {
        if (0 <= from && from < graph->num_vertices && 0 <= to && to < graph->num_vertices) {
            // If the given edgeLabel is equal to or larger than 2; use all edge labels  
            if (2 <= edgeLabel) {  
                    // Add an edge to the already stored vertices in the graph    
                    InitializeNewEdge(graph, from, to, label);
            // If the given edgeLabel is smaller than 2; just use edge labels equal to 1 ("choose the nearest value")
            } else {
                if (label == 1) { 
                    // Add an edge to the already stored vertices in the graph
                    InitializeNewEdge(graph, from, to, label);
                }
            }
        }
    }
    fclose(file);
    return 0; // return statement determines the flow in the main file
}

// Function to initialize a new edge to an existing vertex
void InitializeNewEdge(Graph *graph, int from, int to, int label) {
        Edge* newEdge = (Edge*)malloc(sizeof(Edge));
        if (newEdge == NULL) { // Memory allocation failed; return failure
		    printf("Memory allocation failed!\n");
            return; 
        }
        // Assign the values to their respective structure counterparts
        newEdge->to_vertex = to;
        newEdge->edge_label = label;
        newEdge->next = graph->vertices[from].edges;       
        graph->vertices[from].edges = newEdge;
}

// Function to print out all elements of the adjacency list to the console
void printAdjacencyList(const Graph *graph) {
    for (int i=0; i<graph->num_vertices; i++) {
        printf("Vertex %d: ", i); // print a given vertex i
        Edge *currentEdge = graph->vertices[i].edges;
        while (currentEdge != NULL) { // print all the edges belonging to the chosen vertex i
            printf("(%d, %d) ", currentEdge->to_vertex, currentEdge->edge_label);
            currentEdge = currentEdge->next;
        }
        printf("\n");
    }
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
    }
    free(graph->vertices); // free memory allocated to vertices
}


// Function implementations for the depth first search algorithm using a stack (array implementation)
//
// Function to push an element into the stack (LIFO)
void push(Stack* stack, int value) {
    // Increment the stack pointer (++stackPtr) and then assign a value to it
    stack->array[++stack->top] = value;
}

// Function to pop the last element out of the stack (LIFO)
int pop(Stack* stack) {
    if (stack->top < 0) { // stack array is empty; return NULL
#ifdef DEBUG
        printf("Stack is empty!\n");
#endif
        return 0;
    }
    // Return the top value of the stack and then reduce the stack pointer (stackPtr--)
    return stack->array[stack->top--];
}

// Function to check if the stack (LIFO) is empty
int isEmpty(Stack* stack) {
    // Return a 0 (is not empty) or 1 (is empty) depending on the current stackPtr value
    return (stack->top == -1);
}

// Function to traverse the graph given a certain starting point
void depthFirstSearch(Graph *graph, int startVertex) {
    // Allocating memory for the stack used of the DFS algorithm
    Stack* stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL) { // Memory allocation failed; return failure
		printf("Memory allocation failed!\n");
        return; 
    }
    // Array implemention of the stack where a maxsize is defined (1,000)
    stack->array = (int *)malloc(MAXSIZE * graph->num_vertices * sizeof(int)); 
    stack->top = -1;

    // Push the start vertex onto the stack
    push(stack, startVertex);

    while (!isEmpty(stack)) { // check if the stack is empty
        int currentVertex = pop(stack); // LIFO stack; pop the last element
        graph->vertices[currentVertex].visited = 1; // change the status of the vertex to visited
#ifdef DEBUG
        printf("%d ", currentVertex); // print statement if interested in the algorithm path
#endif
        // Check all connections from the current vertex
        Edge *currentEdge = graph->vertices[currentVertex].edges;
        while (currentEdge != NULL) {
            int nextVertex = currentEdge->to_vertex;
            // If an unvisited connection exist, push it to the stack
            if (graph->vertices[nextVertex].visited == 0) {
                push(stack, nextVertex);  
            }
            currentEdge = currentEdge->next;
        }
    }
    // Free the allocated memory of the stack and its array
    free(stack->array); 
    free(stack);
}

// Function to count the connections between vertices
int countConnectedVertices(Graph *graph) {
    int connectedVerticesCount = 0;

    // Loop over all vertices and check if they have been visited yet
    for (int i=0; i<graph->num_vertices; i++) {
        if (graph->vertices[i].visited == 0) { 
            // Visit connected vertices from the starting point
            depthFirstSearch(graph, i); // start the DFS algorithm
            connectedVerticesCount++; // add one to the counter for a connected component
        }
    }
    return connectedVerticesCount;
}

