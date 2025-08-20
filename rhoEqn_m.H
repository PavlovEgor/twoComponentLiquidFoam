
phi = fvc::flux(U);

{
    fvScalarMatrix rhoUEqn_m
    (
        fvm::ddt(rho) + fvm::div(phi, rho) 
    );

    rhoUEqn_m.solve();
}
