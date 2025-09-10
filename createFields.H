
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


// IOdictionary turbulenceProperties
// (
//     IOobject
//     (
//         "turbulenceProperties",
//         runTime.constant(),
//         mesh,
//         IOobject::MUST_READ_IF_MODIFIED,
//         IOobject::NO_WRITE
//     )
// );

// word simulationType = turbulenceProperties.lookup("simulationType").get<word>();

// dimensionedScalar C_mu
// (
//     "C_mu", caseProperties
// );

// dimensionedScalar C_e1
// (
//     "C_e1", caseProperties
// );

// dimensionedScalar C_e2
// (
//     "C_e2", caseProperties
// );

// dimensionedScalar sig_k
// (
//     "sig_k", caseProperties
// );

// dimensionedScalar sig_e
// (
//     "sig_e", caseProperties
// );

// Info << "Create turbulence fields\n"  << endl;

// volScalarField k
// (
//     IOobject
//     (
//         "k",
//         runTime.timeName(),
//         mesh,
//         IOobject::MUST_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
// );

// volScalarField eps
// (
//     IOobject
//     (
//         "eps",
//         runTime.timeName(),
//         mesh,
//         IOobject::MUST_READ,
//         IOobject::AUTO_WRITE
//     ),
//     mesh
// );

// volScalarField mu_t
// (
//     IOobject
//     (
//         "mu_t",
//         runTime.timeName(),
//         mesh,
//         IOobject::NO_READ,
//         IOobject::NO_WRITE
//     ),
//     (rho0 + rho) * C_mu * (k * k) / eps
// );

// volTensorField gradU = fvc::grad(U);

// volTensorField devR
// (
//     IOobject
//     (
//         "devR",                
//         runTime.timeName(), 
//         mesh,               
//         IOobject::NO_READ,
//         IOobject::NO_WRITE
//     ),
//     mu_t * 0.5 * (gradU + gradU.T()) - (2/3) * mu_t * fvc::div(U) * tensor::I                    
// );


singlePhaseTransportModel laminarTransport(U, phiByRho);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phiByRho, laminarTransport)
);