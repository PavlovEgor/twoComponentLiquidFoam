#ifndef LS
#define LS

#include "constants.h"

void solve_tridiag(int N, double* tmp, double* A, double* B, double* C, double* D);

void solve_square_pentadiag(double * X, struct penta_diag* pd);

#endif