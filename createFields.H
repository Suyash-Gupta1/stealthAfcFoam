
#include "createRDeltaT.H"

Info<< "Reading field p\n" << endl;
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

#include "createPhi.H"


label pRefCell = 0;
scalar pRefValue = 0.0;
setRefCell(p, pimple.dict(), pRefCell, pRefValue);
mesh.setFluxRequired(p.name());


singlePhaseTransportModel laminarTransport(U, phi);

autoPtr<incompressible::turbulenceModel> turbulence
(
    incompressible::turbulenceModel::New(U, phi, laminarTransport)
);

#include "createMRF.H"
#include "createFvOptions.H"

Info<< "\nReading Synthetic Jet Parameters...\n" << endl;

IOdictionary afcProperties
(
    IOobject
    (
        "afcProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

dimensionedScalar jetAmplitude
(
    "jetAmplitude",
    dimensionSet(0, 1, -2, 0, 0, 0, 0),
    afcProperties
);

dimensionedScalar jetFrequency
(
    "jetFrequency",
    dimensionSet(0, 0, -1, 0, 0, 0, 0),
    afcProperties
);

dimensionedVector jetDirection
(
    "jetDirection",
    dimensionSet(0, 0, 0, 0, 0, 0, 0),
    afcProperties
);
