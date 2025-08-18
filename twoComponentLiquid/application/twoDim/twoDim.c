#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "basic_type.h"
#include "step.h"
#include "save.h"
#include "initialize.h"

int main(){
    FILE *output, *input;
    struct sol_param_2D sp;

    input = fopen("../input_par.txt", "r");
    if (input == NULL) {
        perror("Ошибка открытия файла");
        return 1;
    }

    fscanf(input, "%*[^:]: %d", &sp.Nt); // Игнорируем метку, считываем значение
    fscanf(input, "%*[^:]: %d", &sp.Nx);
    fscanf(input, "%*[^:]: %d", &sp.Ny);
    fscanf(input, "%*[^:]: %d", &sp.Ncorr);
    fscanf(input, "%*[^:]: %lf", &sp.u0);
    fscanf(input, "%*[^:]: %lf", &sp.dt);
    fscanf(input, "%*[^:]: %lf", &sp.dx);
    fscanf(input, "%*[^:]: %lf", &sp.dy);
    fscanf(input, "%*[^:]: %lf", &sp.alpha);
    fscanf(input, "%*[^:]: %lf", &sp.rho_1);
    fscanf(input, "%*[^:]: %lf", &sp.rho_2);   

    fclose(input);

    printf("Nt: %d\n", sp.Nt);
    printf("Nx: %d\n", sp.Nx);
    printf("Ny: %d\n", sp.Ny);
    printf("Ncorr: %d\n", sp.Ncorr);
    printf("u0: %lf\n", sp.u0);
    printf("dt: %lf\n", sp.dt);
    printf("dx: %lf\n", sp.dx);
    printf("dy: %lf\n", sp.dy);
    printf("alpha: %lf\n", sp.alpha);
    printf("rho_1: %lf\n", sp.rho_1);
    printf("rho_2: %lf\n", sp.rho_2);

    output = fopen("../rho.txt", "w");

    struct fields_2D fields_prev, fields;

    fields.rho = malloc(sp.Nx * sp.Ny * sizeof(double));
    fields.u   = malloc(sp.Nx * sp.Ny * sizeof(double));
    fields.v   = malloc(sp.Nx * sp.Ny * sizeof(double));
    fields.P   = malloc(sp.Nx * sp.Ny * sizeof(double));
    
    initialize_2D(&sp, &fields);
    save_2D_field(sp.Nx, sp.Ny, fields.v, output);

    for (int i = 0; i < sp.Nt; i++)
    {
        step_implicite_2D(&sp, &fields);
        
        if (i % 1 == 0){
            save_2D_field(sp.Nx, sp.Ny, fields.rho, output);
        }
    }
    fclose(output);
    return 0;
}