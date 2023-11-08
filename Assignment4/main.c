// CSE6010 - Assignment 4
// Collisions
#include "particles.h"

int main(int argc, char *argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 3) {
        printf("Usage: %s <string> <double>\n", argv[0]);
        return 1;
    }

    // Initialize variables to store the user inputs from the command line
    const char *filename = argv[1];   // Input filename
    double end_time = atof(argv[2]);  // End time for the simulation

    // Open the input file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open input file\n");
        return 1;
    }

    int N;  // Number of particles
    double R;  // Particle radius
    double Lx, Ly;  // Box dimensions
    // Read essential simulation parameters from the input file
    fscanf(file, "%d\n%lf\n%lf %lf\n", &N, &R, &Lx, &Ly);

    // Dynamically allocate arrays for particles and potential collisions
    Particle *particles = (Particle*)malloc(N * sizeof(Particle));
    Collision *collision_array = (Collision*)malloc((N * (N + 1) / 2) * sizeof(Collision)); // [pi-wall collision, pi-pj collision]
    int array_size = (N * (N + 1) / 2);

    // Read initial particle information from the file
    for (int i=0; i<N; i++) {
        if(fscanf(file, "%lf %lf %lf %lf\n", &particles[i].x_pos, &particles[i].y_pos, &particles[i].x_vel, &particles[i].y_vel) == 4) {
            particles[i].col_wall = 0; // Track which wall has been part of a collision
            particles[i].num_wall = 0; // Track the number of collisions with walls
            particles[i].num_part = 0; // Track the number of collisions with other particles
        }
    }
    
    fclose(file);

    // Simulation loop & Initialization of necessary variables
    double prev_time = 0.0;
    double current_time = 0.0;

    while (current_time <= end_time) {
        // Initialize the collision_array to calculate potential collisions
        CalculateCollisionArray(particles, collision_array, N, R, Lx, Ly, current_time);

        // Sort the array of potential collision times
        insertionSort(collision_array, array_size);

        // Debugging: Print potential collisions
#ifdef DEBUG
        printCollisionArray(collision_array, N);
#endif
        // Process the earliest potential collision and update the current_time to the collision time
        int k, l; // Indices of particles involved in the collision
        k = collision_array[0].p1;
        l = collision_array[0].p2;
        prev_time = current_time;
        current_time = collision_array[0].time; // Index of the earliest collision in the sorted array

        // Condition to end the program if the simulation time is reached
        if (current_time > end_time) {
            // Update particle positions for the remaining time
            updateAllParticlePosition(particles, N, (end_time - prev_time));
            // Print final particle information
            for (int i=0; i<N; i++) {
                printf("%.6f, %.6f, %d, %d\n", particles[i].x_pos, particles[i].y_pos, particles[i].num_wall, particles[i].num_part);
            }
            // Free dynamically allocated memory
            free(particles);
            free(collision_array);
            return 0;
        }
        // Update the particle positions according to the current time
        updateAllParticlePosition(particles, N, (current_time - prev_time));

        // Update the velocities of the particles involved in a collision
        if (l < 0) {
            // A particle-wall collision occurred
            updateParticleVelocities(&particles[k], &particles[k], k, l);
        } else {
            // A particle-particle collision occurred
            updateParticleVelocities(&particles[k], &particles[l], k, l);
        }
    }
    return 0;
}