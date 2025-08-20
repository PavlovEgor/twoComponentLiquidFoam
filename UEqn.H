// Solve the Momentum equation

// MRF.correctBoundaryVelocity(U);

dimensionedScalar nu("nu", dimensionSet(0, 2, -1, 0, 0, 0, 0), 1e-6);
const scalar half = 0.5;

volVectorField g(
    IOobject(
        "g",
        runTime.constant(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedVector("g", dimAcceleration, vector(0, -9.81, 0)) // Пример: гравитация вниз по оси Y
);


fvVectorMatrix UEqn
(
    fvm::ddt(U) + fvm::div(phi, U)
  // + MRF.DDt(rho, U)
  // + turbulence->divDevRhoReff(U)
  -  nu * fvm::laplacian(U) + half * nu * fvc::grad(fvc::div(U)) - g
);
// fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

// fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == - (1 / rho) * fvc::grad(p));

    // fvOptions.correct(U);
}
