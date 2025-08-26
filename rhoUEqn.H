
{

    fvScalarMatrix rhoUEqn
    (
        fvm::laplacian(rho) + (rho0/D) * fvc::div(U) 
    );

    rhoUEqn.solve();
}
