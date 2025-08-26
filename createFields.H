
Info << "Reading caseProperties" << endl;
IOdictionary caseProperties
(
    IOobject
    (
        "caseProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

dimensionedScalar rho0
(
    "rho0", caseProperties
);

dimensionedScalar nu
(
    "nu", caseProperties
);

dimensionedScalar D
(
    "D", caseProperties
);

dimensionedVector g
(
    "g", caseProperties
);

dimensionedScalar mu = nu * rho0;


Info << "rho0: "    << rho0.value()     << endl;
Info << "nu: "      << nu.value()       << endl;
Info << "D: "       << D.value()        << endl;
Info << "g: "       << g.value()        << endl;

Info<< "Reading field rho\n" << endl;
volScalarField rho
(
    IOobject
    (
        "rho",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field U\n" << endl;
volVectorField U
(
    IOobject
    (
        "U",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field P\n" << endl;
volScalarField p
(
    IOobject
    (
        "p",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);


Info<< "Calculating face flux field phi\n" << endl;

surfaceScalarField phi
(
    IOobject
    (
        "phi",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    linearInterpolate(rho + rho0)*linearInterpolate(U) & mesh.Sf()
);

Info<< "Calculating face flux field phiByRho\n" << endl;

surfaceScalarField phiByRho
(
    IOobject
    (
        "phiByRho",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    fvc::flux(U)
);


mesh.setFluxRequired(p.name());

