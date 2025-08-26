// Solve the Momentum equation



phi = linearInterpolate(rho + rho0)*linearInterpolate(U) & mesh.Sf();

fvVectorMatrix UEqn
(
    fvm::ddt(rho + rho0, U) + fvm::div(phi, U)
  -  mu * fvm::laplacian(U) + 0.5 * mu * fvc::grad(fvc::div(U)) - g * rho
);

UEqn.relax();

if (pimple.momentumPredictor())
{
    solve(UEqn == - fvc::grad(p));

}
