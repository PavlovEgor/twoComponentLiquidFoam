
phiByRho = fvc::flux(U);

{
    fvScalarMatrix rhoUEqn_m
    (
        fvm::ddt(rho) + fvm::div(phiByRho, rho) == fvm::laplacian(D, rho)
    );

    rhoUEqn_m.solve();
}
