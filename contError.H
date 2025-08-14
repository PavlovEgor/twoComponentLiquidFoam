{
    volScalarField tmp_rho(rho);
    dimensionedScalar totalMass = fvc::domainIntegrate(rho);

    #include "rhoEqn.H"

    scalar sumLocalContErr =
        (fvc::domainIntegrate(mag(rho - tmp_rho()))/totalMass).value();

    scalar globalContErr =
        (fvc::domainIntegrate(rho - tmp_rho())/totalMass).value();

    Info<< "time step continuity errors : sum local = " << sumLocalContErr
        << ", global = " << globalContErr
        << endl;
}
