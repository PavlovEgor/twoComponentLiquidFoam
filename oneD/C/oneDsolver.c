#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define Nt      1000
#define Nx      50000
#define Ncorr   1
#define u0      0.0
#define dt      1e-1
#define dx      1e-3
#define alpha   10.0
#define rho_1   1.5
#define rho_2   1.0


void init(double Rho[Nx]){

    for(int i; i < Nx; i++){
        if (i < Nx/8 || i > 3 * Nx/8){
            Rho[i] = rho_2;
        } else if (i < Nx/4)
        {
            Rho[i] = rho_1 + (rho_2 - rho_1) * (Nx/4 - i) * 8 / Nx;
        } else{
            Rho[i] = rho_1 - (rho_2 - rho_1) * (Nx/4 - i) * 8 / Nx;
        }
    }
}

void solve_3_diag(double tmp[Nx], double A[Nx], double B[Nx], double C[Nx], double D[Nx]){
    double P[Nx], Q[Nx];

    P[0] = 1;
    Q[0] = 0;

    for (int i = 1; i < Nx; i++){
        P[i] = - C[i] / (B[i] + A[i] * P[i-1]);
        Q[i] = (D[i] - A[i] * Q[i-1]) / (B[i] + A[i] * P[i-1]);
    }
        
    tmp[Nx-1] = Q[Nx-1];

    for (int i = Nx-2; i >=0; i--){
        tmp[i] = P[i] * tmp[i+1] + Q[i];
    }

}

void step_implicite(double Rho_cur[Nx], double Rho_prev[Nx], int i){
    if (i == 0){
        init(Rho_cur);
    } else {
    
    int j;
    double tmp[Nx];
    double A[Nx];
    double B[Nx];
    double C[Nx];
    double D[Nx];

    A[0] = 0;
    B[0] = 1;
    C[0] = -1;
    D[0] = 0;

    A[Nx-1] = 1;
    B[Nx-1] = -1;
    C[Nx-1] = 0;
    D[Nx-1] = 0;

    for(j=0; j < Nx; j++){
        Rho_prev[j] = Rho_cur[j];
    }

    for(int count = 0; count < Ncorr; count++){
        for (j = 1; j < Nx-1; j++)
        {
            A[j] = -(dt * u0 / (dx * 2)) - Rho_cur[j-1] * (dt * alpha / ((dx * dx) * 4));
            B[j] = 1 + Rho_cur[j] * (dt * alpha / ((dx * dx) * 2));
            C[j] = (dt * u0 / (dx * 2)) - Rho_cur[j+1] * (dt * alpha / ((dx * dx) * 4));
            D[j] = Rho_prev[j];
        }
        solve_3_diag(Rho_cur, A, B, C, D);
    }

}}

void print_line(double Rho[Nx], FILE* file){
    for (int j = 0; j < Nx; j++)
    {
        fprintf(file, "%0.6f ", Rho[j]);
    } 
    fprintf(file, " \n");
}

int main(){
    double Rho_prev[Nx];
    double Rho_cur[Nx];
    FILE *file;

    file = fopen("data.txt", "w");

    for (int i = 0; i < Nt; i++)
    {
        step_implicite(Rho_cur, Rho_prev, i);

        if (i % 10 == 0){
            print_line(Rho_cur, file);
        }
    }

    return 0;
}