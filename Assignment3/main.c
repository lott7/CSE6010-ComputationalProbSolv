// CSE6010 - Assignment 3
// Connected Compontents
#include "all.h"

// #define DEBUG

int main(int argc, char *argv[]) { 
   if (argc != 3) { // output if the user fails to give a wrong argument
        printf("Usage: %s <string> <integer>\n", argv[0]);
        return 1;
    }
    // Initialize variables to store the user inputs from the command line
    const char *filename = argv[1];
    int edgeLabel = atoi(argv[2]);

    // Print the values which have been written on the command line
#ifdef DEBUG
    printf("Integer: %d\n", edgeLabel);
    printf("String: %s\n", filename);
#endif

    // Implementation of the graph from a given input file
    Graph graph;
    if (readGraphFile(filename, edgeLabel, &graph)) {
#ifdef DEBUG
        printf("Failed to load the graph from the file.\n");
#endif
        return 1;
    }

    // Print the stored graph to the console
#ifdef DEBUG
    printf("Adjacency List:\n");
    printAdjacencyList(&graph);
#endif

    // Count the connected componets in the graph
    int connectedComponents = countConnectedVertices(&graph);
    printf("%d\n", connectedComponents);

    // Print the number of connected componets to the console
#ifdef DEBUG 
    printf("Number of connected components: %d\n", connectedComponents);
# endif

    // Free the memory allocated for the graph
    freeGraphMemory(&graph);
    
    return 0;
}
