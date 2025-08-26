{
    volScalarField rAU(1.0/UEqn.A());
    volVectorField HbyA("HbyA", U);
    HbyA = rAU*UEqn.H();
    surfaceScalarField phiHbyA("phiHbyA", fvc::flux(HbyA));


    // Define coefficients and pseudo-velocities for RCM interpolation
    // M[U] = AU - H = -grad(p)
    // U = H/A - 1/A grad(p)
    // H/A = U + 1/A grad(p)

    surfaceScalarField rAUf
    (
        "rhorAUf",
        1 / (fvc::interpolate(UEqn.A()))
    );

    // Non-orthogonal pressure corrector loop
    while (pimple.correctNonOrthogonal())
    {
        // Pressure corrector
        fvScalarMatrix pEqn
        (
            fvm::laplacian(rAUf, p) ==
            (D / rho0) * fvc::laplacian(rho)
                + fvc::div(phiHbyA)
            
        );

        pEqn.solve(p.select(pimple.finalInnerIter()));


    }

    // Explicitly relax pressure for momentum corrector
    p.relax();

    U = HbyA - rAU*fvc::grad(p);
    U.correctBoundaryConditions();
    fvOptions.correct(U);

}

