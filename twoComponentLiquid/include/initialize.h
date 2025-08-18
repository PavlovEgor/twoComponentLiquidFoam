#ifndef INIT
#define INIT
#include "constants.h"

void initialize_1D(int N, double* Rho, double rho_1, double rho_2);

void initialize_2D(struct sol_param_2D* sp, struct fields_2D* fields);

void initialize_3D();

#endif