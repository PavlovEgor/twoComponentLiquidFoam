autoPtr<fluidThermo> pThermo
(
    fluidThermo::New(mesh)
);
fluidThermo& thermo = pThermo();
thermo.validate(args.executable(), "h", "e");

        
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
    linearInterpolate(rho)*linearInterpolate(U) & mesh.Sf()
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
    phi/linearInterpolate(rho)
);

// Info<< "Creating turbulence model\n" << endl;
// autoPtr<compressible::turbulenceModel> turbulence
// (
//     compressible::turbulenceModel::New
//     (
//         rho,
//         U,
//         phi,
//         thermo
//     )
// );

mesh.setFluxRequired(p.name());

#include "createMRF.H"

// Info<< "Creating compressibility field psi\n" << endl;
// volScalarField psi("psi", 1.0/((thermo.Cp() - thermo.Cv())*T));
// psi.oldTime() = 1.0/((thermo.Cp() - thermo.Cv())*T.oldTime());
// psi.oldTime().oldTime() = 1.0/((thermo.Cp()-thermo.Cv())*T.oldTime().oldTime());
