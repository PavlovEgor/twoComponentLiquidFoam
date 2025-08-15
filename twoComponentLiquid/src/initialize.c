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

