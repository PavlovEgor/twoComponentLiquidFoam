
phi = linearInterpolate(rho + rho0)*linearInterpolate(U) & mesh.Sf();
gradU = fvc::grad(U);
volScalarField Pk = mu * 0.5 * (gradU + gradU.T()) && gradU;

{
    fvScalarMatrix epsEqn
    (
        fvm::ddt(rho0 + rho, eps) + fvm::div(phi, eps) == fvm::laplacian(mu + (mu_t / sig_e), eps) + C_e1 * eps * Pk / k - C_e2 * (rho0 + rho) * eps * eps / k
    );

    epsEqn.solve();
}


{
    fvScalarMatrix kEqn
    (
        fvm::ddt(rho0 + rho, k) + fvm::div(phi, k) == fvm::laplacian(mu + (mu_t / sig_k), k) + Pk - (rho0 + rho) * eps
    );

    kEqn.solve();
}


