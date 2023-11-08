#ifndef PARTICLES_H
#define PARTICLES_H

#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

// Typedef and function definitions for solving assignment 4 "collisions"

// Particle structure
typedef struct particles {
    double x_pos;  // x-position
    double y_pos;  // y-position
    double x_vel;  // x-velocity
    double y_vel;  // y-velocity
    int col_wall;  // Wall which has been hit by the particle (0: {Default}, 1: {L, R}, 2: {U, D})
    int num_wall;  // Number of wall collisions
    int num_part;  // Number of particle collisions
} Particle;

// Collision array structure
typedef struct collisions {
    int p1;        // Index of particle 1
    int p2;        // Index of particle 2
    double time;   // Collision time
} Collision;

// Function definitions for collision calculations and related operations
double calculateWallCollision(Particle *p, double Ly, double Lx, double R, double current_time);
double calculateParticleCollision(Particle *p1, Particle *p2, double R, double t_r);
void updateAllParticlePosition(Particle *p, int numParticles, double time);
void updateParticleVelocities(Particle *p1, Particle *p2, int particle1, int particle2);
void CalculateCollisionArray(Particle *particles, Collision *collision_array, int array_size, double R, double Ly, double Lx, double current_time);
void insertionSort(Collision *collision_array, int array_size);
void printCollisionArray(Collision *collision_array, int numParticles);

#endif