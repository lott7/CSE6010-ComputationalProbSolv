#include <stdio.h>
#include <math.h>
#define MAXITERATIONS 50
#define EPSILON 1e-10

/*
status:
    0: success
    1: max iterations reached
    2: singular jacobian
    3: negative in sqrt
    4: not implemented
*/

void newton_method(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;
    double x_n, y_n;

    while (*iterations < MAXITERATIONS) {
        if (((42* *y *2* *x) - (2* *y *10* *x)) == 0) { // status check: singular jacobian
            *status = 2;
            break;
        } else {
            x_n = *x - (1 / ((42* *y *2* *x) - (2* *y *10* *x))) *  // mathematical formulations
                        (42* *y *(pow(*x, 2) + pow(*y, 2) - 1) - 2* *y *(5*pow(*x, 2) + 21*pow(*y, 2) - 9));

            y_n = *y - (1 / ((42* *y * 2* *x) - (2* *y * 10* *x))) * 
                        (-10* *x *(pow(*x, 2) + pow(*y, 2) - 1) + 2* *x *(5* pow(*x, 2) + 21*pow(*y, 2) - 9));
        }

        if (fabs(*x - x_n) < EPSILON && fabs(*y - y_n) < EPSILON) { // status check: convergence criteria
            *status = 0;
            break;
        }

        *x = x_n; // updating the pointers
        *y = y_n;
        *iterations = ++*iterations; // counting iteration steps

        if (*iterations == MAXITERATIONS) { // status check: max iterations reached 
            *status = 1;
        }
    }
}


void fixed_point_iteration(double x0, double y0, double* x, double* y, int* iterations, int* status) {
    *x = x0;
    *y = y0;
    *iterations = 0;
    *status = 4;
    double x_n, y_n;

    while (*iterations < MAXITERATIONS) { 
        if (pow(*y, 2) > 1 || 9 < 5 * pow(*x, 2)) { // status check: negative in sqrt
            *status = 3;
            break;
        } else {
            x_n = sqrt(1 - pow(*y, 2)); // mathematical formulations
            y_n = (1 / sqrt(21)) * sqrt(9 - 5 * pow(*x, 2));
        }

        if (fabs(*x - x_n) < EPSILON && fabs(*y - y_n) < EPSILON) { // status check: convergence criteria
            *status = 0;
            break;
        }

        *x = x_n; // updating the pointers
        *y = y_n;
        *iterations = ++*iterations; // counting iteration steps

        if (*iterations == MAXITERATIONS) { // status check: max iterations reached (0 to 49 = 50 iterations)
        *status = 1;
        }
    }     
}
