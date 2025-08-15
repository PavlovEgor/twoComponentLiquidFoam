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

#endif