#include "save.h"

void save_1D_field(int N, double* Rho, FILE* output){
    for (int j = 0; j < N; j++)
    {
        fprintf(output, "%0.6f ", Rho[j]);
    } 
    fprintf(output, " \n");
}

void save_2D_field(int Nx, int Ny, double* field, FILE* output){
    for (int j = 0; j < Nx * Ny; j++)
    {
        fprintf(output, "%0.6f ", field[j]);
    } 
    fprintf(output, " \n");
}