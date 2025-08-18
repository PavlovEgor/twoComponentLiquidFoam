#include "LS_solvers.h"

void solve_tridiag(int N, double* tmp, double* A, double* B, double* C, double* D){
    double* P   = malloc(N * sizeof(double));
    double* Q   = malloc(N * sizeof(double));

    P[0] = 1;
    Q[0] = 0;

    for (int i = 1; i < N; i++){
        P[i] = - C[i] / (B[i] + A[i] * P[i-1]);
        Q[i] = (D[i] - A[i] * Q[i-1]) / (B[i] + A[i] * P[i-1]);
    }
        
    tmp[N-1] = Q[N-1];

    for (int i = N-2; i >=0; i--){
        tmp[i] = P[i] * tmp[i+1] + Q[i];
    }

    free(P);
    free(Q);
}


void solve_square_pentadiag(double * X, struct penta_diag* pd){
    double**  G = malloc(pd -> Nx * sizeof(double *));
    double*** H = malloc(pd -> Nx * sizeof(double **));
    double*   C = malloc(pd -> Ny * sizeof(double));
    double*   R = malloc(pd -> Ny * sizeof(double));
    double**  D = malloc(pd -> Nx * sizeof(double *));
    
    for (int i = 0; i < pd->Nx; i++)
    {
        G[i] = malloc(pd -> Ny * sizeof(double));
        H[i] = malloc(pd -> Ny * sizeof(double *));

        for (int j = 0; j < pd -> Ny; j++)
        {
            H[i][j] = malloc(pd -> Ny * sizeof(double));
        }
    }
    for (int j = 0; j < pd -> Ny; j++)
    {
        D[j] = malloc((j + 1) * sizeof(double));
    }
    



}