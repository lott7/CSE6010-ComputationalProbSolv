// CSE6010 - Assignment 5
// Bellman-Ford with OpenMP
#include "bellmanford.h"

// Commented out for DEBUG mode, uncomment to enable debugging
// #define DEBUG

int main(int argc, char * argv[]) {
    if (argc != 4 && argc != 3) {
        printf("Usage: %s <file_name> <num_threads> <num_destination>\n", argv[0]);
        return 1;
    }

    // Read command-line arguments
    const char *file_name;
    int num_threads, destination_vertex;

    // Check if the number of command-line arguments is equal to 4
    if (argc == 4) {
        // If true, convert the fourth command-line argument to an integer and assign it to destination_vertex
        file_name = argv[1];
        num_threads = atoi(argv[2]);
        destination_vertex = atoi(argv[3]);
    } else {
        // If false, assign -1 to destination_vertex
        file_name = argv[1];
        num_threads = atoi(argv[2]);
        destination_vertex = -1;
    }
    // Set the number of threads
    omp_set_num_threads(num_threads);

    // Open the input file
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Error: Unable to open input file\n");
        return 1;
    }

    // Implementation of the graph from a given input file 
    Graph graph;
    readGraphFile(file_name, &graph);

    // Print the stored graph to the console (optional, for debugging)
#ifdef DEBUG
    printf("Adjacency List:\n");
    printAdjacencyList(&graph);
#endif

    // Applying the Bellman-Ford algorithm to find the shortest path
    bellmanFord(&graph, num_threads, 0, destination_vertex);

    // Free the memory allocated for the graph
    freeGraphMemory(&graph);

    return 0;
}
