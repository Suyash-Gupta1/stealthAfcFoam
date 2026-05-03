// Solve the Momentum equation

MRF.correctBoundaryVelocity(U);

// --- OUR CUSTOM STEALTH JET MATH ---
scalar waveMultiplier = Foam::sin(2.0 * constant::mathematical::pi * jetFrequency.value() * runTime.value());
dimensionedScalar sinWave("sinWave", dimless, waveMultiplier);

volVectorField syntheticJetSource
(
    IOobject
    (
        "syntheticJetSource",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    jetDirection * jetAmplitude * sinWave
);
// -----------------------------------

tmp<fvVectorMatrix> tUEqn
(
    fvm::ddt(U)
  + fvm::div(phi, U)
  + MRF.DDt(U)
  + turbulence->divDevReff(U)
 ==
    fvOptions(U)
  + syntheticJetSource
);

fvVectorMatrix& UEqn = tUEqn.ref();

UEqn.relax();

fvOptions.constrain(UEqn);

if (pimple.momentumPredictor())
{
    solve(UEqn == -fvc::grad(p));

    fvOptions.correct(U);
}
