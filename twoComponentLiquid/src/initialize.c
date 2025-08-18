#include "initialize.h"


void initialize_1D(int N, double* Rho, double rho_1, double rho_2){
    for(int i; i < N; i++){
        if (i < N/8 || i > 3 * N/8){
            Rho[i] = rho_2;
        } else if (i < N/4)
        {
            Rho[i] = rho_1 + (rho_2 - rho_1) * (N/4 - i) * 8 / N;
        } else{
            Rho[i] = rho_1 - (rho_2 - rho_1) * (N/4 - i) * 8 / N;
        }
    }
}

void initialize_2D(struct sol_param_2D* sp, struct fields_2D* fields){
    int Nx, Ny;
    Nx = sp -> Nx;
    Ny = sp -> Ny;

    double R_max = (Nx / 2) * sp -> dx;
    double r;

    for (int i = 0; i < Nx; i++)
    {
        for (int j = 0; j < Ny; j++)
        {
            r = hypot((Nx/2 - i) * sp -> dx, (Ny/2 - j) * sp -> dy);
            if (r < R_max){
                fields -> rho[j + Ny * i] = sp -> rho_1 + (sp -> rho_2 - sp -> rho_1) * r / R_max;
            } else{
                fields -> rho[j + Ny * i] = sp -> rho_2;
            }
            
            fields -> u[j + Ny * i] = 0;
            fields -> v[j + Ny * i] = (sp -> u0) * (1 - ((Nx/2 - i) * sp -> dx) * ((Nx/2 - i) * sp -> dx) / (R_max * R_max));
            fields -> P[j + Ny * i] = 0;
        }
    }

    for (int i = 0; i < Nx; i++)
    {
        fields -> rho[Ny * i] = fields -> rho[1 + Ny * i];
        fields -> rho[Nx - 1 + Ny * i] = fields -> rho[Nx - 2 + Ny * i];
    }

    for (int j = 0; j < Ny; j++)
    {
        fields -> rho[j] = fields -> rho[j + Ny];
        fields -> rho[j + Ny * (Nx - 1)] = fields -> rho[j + Ny * (Nx - 2)];
    }
}