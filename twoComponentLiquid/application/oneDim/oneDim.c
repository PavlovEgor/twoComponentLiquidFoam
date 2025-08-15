#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "basic_type.h"
#include "step.h"
#include "save.h"


int main(){
    FILE *output, *input;
    struct sol_param_1D sp;

    input = fopen("../input_par.txt", "r");
    if (input == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fscanf(input, "%d", &sp.Nt);
    fscanf(input, "%d", &sp.Nx);
    fscanf(input, "%d", &sp.Ncorr);
    fscanf(input, "%lf", &sp.u0);
    fscanf(input, "%lf", &sp.dt);
    fscanf(input, "%lf", &sp.dx);
    fscanf(input, "%lf", &sp.alpha);
    fscanf(input, "%lf", &sp.rho_1);
    fscanf(input, "%lf", &sp.rho_2);    

    fclose(input);

    printf("Nt: %d\n", sp.Nt);
    printf("Nx: %d\n", sp.Nx);
    printf("Ncorr: %d\n", sp.Ncorr);
    printf("u0: %lf\n", sp.u0);
    printf("dt: %lf\n", sp.dt);
    printf("dx: %lf\n", sp.dx);
    printf("alpha: %lf\n", sp.alpha);
    printf("rho_1: %lf\n", sp.rho_1);
    printf("rho_2: %lf\n", sp.rho_2);

    output = fopen("../data.txt", "w");

    double* Rho_prev  = malloc(sp.Nx * sizeof(double));
    double* Rho_cur   = malloc(sp.Nx * sizeof(double));

    for (int i = 0; i < sp.Nt; i++)
    {
        step_implicite_1D(&sp, Rho_cur, Rho_prev, i);
        if (i % 10 == 0){
            save_1D_field(sp.Nx, Rho_cur, output);
        }
    }
    fclose(output);
    return 0;
}