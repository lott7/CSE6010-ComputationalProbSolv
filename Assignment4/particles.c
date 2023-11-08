#include "particles.h"

// Commented out for DEBUG mode, uncomment to enable debugging
// #define DEBUG

// Function to calculate the time of the particle-wall collision
double calculateWallCollision(Particle *p, double Lx, double Ly, double R, double current_time) {
    double t_L, t_R, t_U, t_D;
    t_L = t_R = t_U = t_D = DBL_MAX; // Initialize time variables
    double x_time, y_time; // Temporary variables to store collision times

    // Calculate the time it takes to reach a wall in the x or y direction
    if (p->x_vel < 0) { // Particle moving left
        x_time = (R - p->x_pos) / p->x_vel;
        if (x_time >= 0 && x_time < t_L) {
            t_L = x_time;
        }
    } else if (p->x_vel > 0) { // Particle moving right
        x_time = ((Lx - R) - p->x_pos) / p->x_vel;
        if (x_time >= 0 && x_time < t_R) {
            t_R = x_time;
        }
    }
    if (p->y_vel < 0) { // Particle moving downward
        y_time = (R - p->y_pos) / p->y_vel;
        if (y_time >= 0 && y_time < t_D) {
            t_D = y_time;
        }
    } else if (p->y_vel > 0) { // Particle moving upward
        y_time = ((Ly - R) - p->y_pos) / p->y_vel;
        if (y_time >= 0 && y_time < t_U) {
            t_U = y_time;
        }
    }
    // Calculate the minimum in each direction
    double min_x = fmin(t_L, t_R);
    double min_y = fmin(t_U, t_D);

    // Determine the direction of the collision and assign col_wall accordingly
    if (min_x < DBL_MAX || min_y < DBL_MAX) {
        if (min_x < min_y) {
            p->col_wall = 1; // Collision with left or right wall
        } else {
            p->col_wall = 2; // Collision with upper or lower wall
        }
    } else {
        p->col_wall = 0; // No collision
    }

#ifdef DEBUG
    printf("Particle col_wall value: %d\n", p->col_wall);
#endif

    // Return the minimum of the horizontal and vertical collision times and add the current_time
    return current_time + fmin(min_x, min_y);
}

// Function to calculate the time of particle-particle collisions
double calculateParticleCollision(Particle *p1, Particle *p2, double R, double current_time) {
    // Constants and unknown values
    double tc = 0; // Unknown collision time
    double discriminant, tc1, tc2;
    
    // Calculate the coefficients for the quadratic equation
    double A = pow(p1->x_vel - p2->x_vel, 2) + pow(p1->y_vel - p2->y_vel, 2);
    double B = 2 * ((p1->x_pos - p2->x_pos) * (p1->x_vel - p2->x_vel) + (p1->y_pos - p2->y_pos) * (p1->y_vel - p2->y_vel));
    double C = pow(p1->x_pos - p2->x_pos, 2) + pow(p1->y_pos - p2->y_pos, 2) - 4 * R * R;

    // Calculate the discriminant
    discriminant = B * B - 4 * A * C;

    if (discriminant < 0) {
        // No real solution, particles won't collide
#ifdef DEBUG
        printf("No real solution. Particles won't collide.\n");
#endif
        return DBL_MAX;
    } else {
        // Calculate t1 and t2 using the quadratic formula
        tc1 = (-B - sqrt(discriminant)) / (2 * A);
        tc2 = (-B + sqrt(discriminant)) / (2 * A);

        // Choose the smaller positive root
        if (tc1 >= 0 && tc2 >= 0) {
            tc = fmin(tc1, tc2);
        } else {
            // Both roots are negative, which means they won't collide
#ifdef DEBUG
            printf("No positive solutions. Particles won't collide.\n");
#endif
            return DBL_MAX;
        }
    }  
    // Add tc to current_time to get the final collision time
    tc = current_time + tc;
#ifdef DEBUG
        printf("Collision time (tc): %.6f\n", tc);
#endif

    return tc;
}

// Function to update particle velocities after a collision
void updateParticleVelocities(Particle *p1, Particle *p2, int particle1, int particle2) {
    // Check if a particle-wall collision happened
    if (particle2 == -1) {
        p1->num_wall += 1; // Increment the wall collision count for p1

        // Reverse the sign of the velocity component based on the wall collision direction
        if (p1->col_wall == 1) {
            p1->x_vel = -p1->x_vel; // Reverse x-velocity
        } else {
            p1->y_vel = -p1->y_vel; // Reverse y-velocity
        }
        p1->col_wall = 0; // Reset the wall component to the default value

    // A particle-particle collision happened
    } else {
        p1->num_part += 1; // Increment the particle-particle collision count for p1
        p2->num_part += 1; // Increment the particle-particle collision count for p2

        // Swap x and y velocities between the two particles to simulate the collision
        double temp_x_vel = p1->x_vel;
        double temp_y_vel = p1->y_vel;
        
        p1->x_vel = p2->x_vel;
        p1->y_vel = p2->y_vel;
        p2->x_vel = temp_x_vel;
        p2->y_vel = temp_y_vel;
    }
}

// Function to update all particle positions given a time
void updateAllParticlePosition(Particle *p, int numParticles, double time) {
    for (int i=0; i<numParticles; i++) {
        // Update the particle positions based on their velocities and the given time
        p[i].x_pos += p[i].x_vel * time;
        p[i].y_pos += p[i].y_vel * time;
    }
}

// Function to initialize and update the collision array and calculate the potential collision times of all components
void CalculateCollisionArray(Particle *particles, Collision *collision_array, int numParticles, double R, double Ly, double Lx, double current_time) {
    int index = 0;
    double collision_time;

    for (int i=0; i<numParticles; i++) {
        for (int j=i; j<numParticles; j++) {
            if (i == j) {
                // Calculate the time of collision between particle i and the wall
                collision_time = calculateWallCollision(&particles[i], Ly, Lx, R, current_time);

                // Store the collision information in the collision_array
                collision_array[index].p1 = i; // Index of the first particle
                collision_array[index].p2 = -1; // Indicate no particle-particle collision with -1
                collision_array[index].time = collision_time; // Store the collision time
                index++;
            } else {
                // Calculate the time of collision between particles i and j
                collision_time = calculateParticleCollision(&particles[i], &particles[j], R, current_time);

                // Store the collision information in the collision_array
                collision_array[index].p1 = i; // Index of the first particle
                collision_array[index].p2 = j; // Index of the second particle
                collision_array[index].time = collision_time; // Store the collision time
                index++;
            }
        }
    }
}

// Function to sort an array in place using the insertion sort algorithm
void insertionSort(Collision *array, int array_size) {
    int i, j;
    Collision key;

    for (i=1; i<array_size; i++) {
        key = array[i];
        j = i - 1;

        // Compare and move elements to sort the array
        while (j >= 0 && array[j].time > key.time) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key; // Place the current element in the correct position
    }
}

// Function to print out the contents of the collision_array
void printCollisionArray(Collision *collision_array, int numParticles) {
    int index = 0; // Initialize the index for the collision_array
    for (int i=0; i<numParticles; i++) {
        for (int j=i; j<numParticles; j++) {
            // Print information about each collision
            printf("Collision between particles %d and %d at time %.6f seconds\n", collision_array[index].p1, collision_array[index].p2, collision_array[index].time);
            index++;
        }
    }
}