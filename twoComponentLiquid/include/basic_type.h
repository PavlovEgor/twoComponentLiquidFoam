#ifndef BT
#define BT

struct sol_param_1D {
    int Nt;
    int Nx;
    int Ncorr;
    double u0;
    double dt;
    double dx;
    double alpha;
    double rho_1;
    double rho_2;
};

struct sol_param_2D {
    int Nt;
    int Nx;
    int Ny;
    int Ncorr;
    double u0;
    double dt;
    double dx;
    double dy;
    double alpha;
    double rho_1;
    double rho_2;
};

struct penta_diag {
    int Nx;
    int Ny;

    double * N;
    double * E;
    double * S;
    double * W;

    double * B;
};

struct fields_2D
{
    double * rho;
    double * u;
    double * v;
    double * P;
};


#endif