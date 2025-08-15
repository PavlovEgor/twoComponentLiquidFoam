#include "step.h"
#include "LS_solvers.h"

void step_implicite_1D(struct sol_param_1D* sp, double* Rho_cur, double* Rho_prev, int i){

    int j;
    double* tmp = malloc(sp -> Nx * sizeof(double));
    double* A   = malloc(sp -> Nx * sizeof(double));
    double* B   = malloc(sp -> Nx * sizeof(double));
    double* C   = malloc(sp -> Nx * sizeof(double));
    double* D   = malloc(sp -> Nx * sizeof(double));



    A[0] = 0;
    B[0] = 1;
    C[0] = -1;
    D[0] = 0;

    A[sp -> Nx-1] = 1;
    B[sp -> Nx-1] = -1;
    C[sp -> Nx-1] = 0;
    D[sp -> Nx-1] = 0;

    for(j=0; j < sp -> Nx; j++){
        Rho_prev[j] = Rho_cur[j];
    }

    for(int count = 0; count < sp -> Ncorr; count++){
        for (j = 1; j < sp -> Nx-1; j++)
        {
            A[j] = -(sp -> dt * sp -> u0 / (sp -> dx * 2)) - Rho_cur[j-1] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 4));
            B[j] = 1 + Rho_cur[j] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 2));
            C[j] = (sp -> dt * sp -> u0 / (sp -> dx * 2)) - Rho_cur[j+1] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 4));
            D[j] = Rho_prev[j];
        }
        solve_tridiag(sp -> Nx, tmp, A, B, C, D);
    }

    free(A);
    free(B);
    free(C);
    free(D);
    free(tmp);
}