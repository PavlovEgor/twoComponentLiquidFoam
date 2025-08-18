#ifndef SOL
#define SOL

#include "constants.h"

void step_implicite_1D(struct sol_param_1D* sp, double* Rho);

void step_implicite_2D(struct sol_param_2D* sp, struct fields_2D* fields);

#endif