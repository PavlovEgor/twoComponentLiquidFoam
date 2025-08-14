// Solve the Momentum equation

// MRF.correctBoundaryVelocity(U);

dimensionedScalar mu("mu", dimensionSet(1, -1, -1, 0, 0, 0, 0), 0.1);





tmp<fvVectorMatrix> tUEqn
(
    fvm::ddt(rho, U) + fvm::div(phi, U)
  // + MRF.DDt(rho, U)
  // + turbulence->divDevRhoReff(U)
  -  mu * fvm::laplacian(U)
 ==
    fvOptions(rho, U)
);
fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
