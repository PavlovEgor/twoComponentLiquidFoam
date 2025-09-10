// Solve the Momentum equation


phi = linearInterpolate(rho + rho0)*linearInterpolate(U) & mesh.Sf();
// gradU = fvc::grad(U);
// mu_t = (rho0 + rho) * C_mu * (k * k) / eps;
// devR = mu_t * 0.5 * (gradU + gradU.T()) - (2/3) * mu_t * fvc::div(U) * tensor::I  ;

fvVectorMatrix UEqn
(
    fvm::ddt(rho + rho0, U) + fvm::div(phi, U) + (rho + rho0) * turbulence->divDevReff(U)
   - g * rho
);

UEqn.relax();

if (pimple.momentumPredictor())
{
    solve(UEqn == - fvc::grad(p));

}
