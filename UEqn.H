// Solve the Momentum equation

// MRF.correctBoundaryVelocity(U);

dimensionedScalar nu("nu", dimensionSet(0, 2, -1, 0, 0, 0, 0), 1e-6);
dimensionedScalar mu("mu", dimensionSet(1, -1, -1, 0, 0, 0, 0), 1e-3);

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

phi = linearInterpolate(rho + rho2)*linearInterpolate(U) & mesh.Sf();

fvVectorMatrix UEqn
(
    fvm::ddt(rho + rho2, U) + fvm::div(phi, U)
  // + MRF.DDt(rho, U)
  // + turbulence->divDevRhoReff(U)
  -  mu * fvm::laplacian(U) + half * mu * fvc::grad(fvc::div(U)) - rho * g
);
// fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

// fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == - fvc::grad(p));

    // fvOptions.correct(U);
}
