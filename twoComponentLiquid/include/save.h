#ifndef SAVE
#define SAVE

#include "constants.h"

void save_1D_field(int N, double* Rho, FILE* output);

void save_2D_field(int Nx, int Ny, double* field, FILE* output);

#endif