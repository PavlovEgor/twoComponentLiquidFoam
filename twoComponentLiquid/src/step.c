#include "step.h"
#include "LS_solvers.h"

void step_implicite_1D(struct sol_param_1D* sp, double* Rho){

    int j;
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

    for(j=1; j < sp -> Nx-1; j++){
        D[j] = Rho[j];
    }

    for(int count = 0; count < sp -> Ncorr; count++){
        for (j = 1; j < sp -> Nx-1; j++)
        {
            A[j] = -(sp -> dt * sp -> u0 / (sp -> dx * 2)) - Rho[j-1] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 4));
            B[j] = 1 + Rho[j] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 2));
            C[j] = (sp -> dt * sp -> u0 / (sp -> dx * 2)) - Rho[j+1] * (sp -> dt * sp -> alpha / ((sp -> dx * sp -> dx) * 4));
        }
        solve_tridiag(sp -> Nx, Rho, A, B, C, D);
    }

    free(A);
    free(B);
    free(C);
    free(D);
}

void pEqn_2D(){}

void UEqn_2D(){
}

void VEqn_2D(){}

void rhoEqn_2D(struct sol_param_2D* sp, double * U, double * V, double * rho){
    struct penta_diag pd;

    int i, j;

    pd.Nx = sp -> Nx;
    pd.Ny = sp -> Ny;

    pd.N = malloc(pd.Nx * pd.Ny * sizeof(double));
    pd.E = malloc(pd.Nx * pd.Ny * sizeof(double));
    pd.S = malloc(pd.Nx * pd.Ny * sizeof(double));
    pd.W = malloc(pd.Nx * pd.Ny * sizeof(double));
    pd.B = malloc(pd.Nx * pd.Ny * sizeof(double));

    for (j = 0; j < pd.Ny; j++)
    {
        pd.N[j] = 0;
        pd.E[j] = 0;
        pd.W[j] = 0;
        pd.S[j] = -1;
        pd.B[j] = 0;

        pd.S[j + pd.Ny * (pd.Nx - 1)] = 0;
        pd.E[j + pd.Ny * (pd.Nx - 1)] = 0;
        pd.W[j + pd.Ny * (pd.Nx - 1)] = 0;
        pd.N[j + pd.Ny * (pd.Nx - 1)] = -1;
        pd.B[j + pd.Ny * (pd.Nx - 1)] = 0;
    }

    for (i = 0; i < pd.Nx; i++)
    {
        pd.N[pd.Ny * i] = 0;
        pd.E[pd.Ny * i] = -1;
        pd.W[pd.Ny * i] = 0;
        pd.S[pd.Ny * i] = 0;
        pd.B[pd.Ny * i] = 0;

        pd.N[pd.Ny-1 + pd.Ny * i] = 0;
        pd.E[pd.Ny-1 + pd.Ny * i] = 0;
        pd.W[pd.Ny-1 + pd.Ny * i] = -1;
        pd.S[pd.Ny-1 + pd.Ny * i] = 0;
        pd.B[pd.Ny-1 + pd.Ny * i] = 0;
    }

    for (i = 1; i < pd.Nx-1; i++)
    {
        for (j = 1; i < pd.Ny-1; j++)
        {
            pd.N[j + pd.Ny * i] = - (sp -> dt / (2 * sp -> dx)) * U[j + pd.Ny * (i - 1)];
            pd.E[j + pd.Ny * i] = (sp -> dt / (2 * sp -> dy)) * V[j + 1 + pd.Ny * (i)];
            pd.S[j + pd.Ny * i] = (sp -> dt / (2 * sp -> dx)) * U[j + pd.Ny * (i + 1)];
            pd.W[j + pd.Ny * i] = - (sp -> dt / (2 * sp -> dy)) * V[j - 1 + pd.Ny * (i)];
            pd.B[j + pd.Ny * i] = rho[j + pd.Ny * i];
        }
    }

    solve_square_pentadiag(rho, &pd);

    free(&pd);
}


void step_implicite_2D(struct sol_param_2D* sp, struct fields_2D* fields){
    struct penta_diag pd;

    
}