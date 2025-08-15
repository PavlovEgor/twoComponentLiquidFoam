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
