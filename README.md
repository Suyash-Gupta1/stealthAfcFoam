# stealthAfcFoam: Active Flow Control (AFC) Solver for OpenFOAM

A custom transient, incompressible Navier-Stokes solver for OpenFOAM developed to simulate Zero-Net-Mass-Flux (ZNMF) synthetic jets. This solver is designed for aerospace and automotive R&D applications, specifically targeting flow separation delay and boundary layer manipulation without the use of physical control surfaces (e.g., stealth UAV maneuvering).

## 🚀 Key Features

* **Implicit Momentum Source:** Injects an oscillatory, time-dependent momentum source term directly into the `UEqn`, bypassing the massive computational overhead of dynamic meshing.
* **Transient Stability:** Built on the `pimpleFoam` architecture, allowing for stable calculations at high Courant numbers ($Co > 1$) during high-frequency jet pulses.
* **Runtime Modifiable Parameters:** Features custom `IOdictionary` integration. Jet amplitude, frequency, and directional vectors are read dynamically from a configuration file, eliminating the need to recompile C++ code between test runs.
* **Unit-Safe Architecture:** Fully complies with OpenFOAM's strict dimensional checking protocols using `dimensionedScalar` and `.value()` extractions.

## 🧮 Mathematical Formulation

Physical synthetic jets operate by rhythmically ingesting and expelling fluid through an orifice. Over a complete cycle, the net mass flux is zero, but a non-zero net momentum is imparted to the boundary layer.

This solver models the actuator mathematically as a momentum source ($S_M$) added to the right-hand side of the momentum equation:

$S_M = \vec{d} \cdot A \cdot \sin(2\pi f t)$

Where:
* $\vec{d}$ = Unit direction vector of the jet
* $A$ = Amplitude / Strength of the pulse ($m/s^2$)
* $f$ = Actuation frequency ($Hz$)
* $t$ = Instantaneous simulation time ($s$)

## 🛠️ Installation & Compilation

**Prerequisites:** OpenFOAM (Tested on v2312)

1. Clone the repository into your OpenFOAM user applications directory:
   ```bash
   mkdir -p $WM_PROJECT_USER_DIR/applications
   cd $WM_PROJECT_USER_DIR/applications
   git clone [https://github.com/Suyash-Gupta1/stealthAfcFoam.git](https://github.com/Suyash-Gupta1/stealthAfcFoam.git)
   cd stealthAfcFoam

Compile the custom C++ solver:


wmake

The executable will be placed in your $FOAM_USER_APPBIN directory.

Usage & Configuration

To use stealthAfcFoam in a case, you must define the synthetic jet parameters.

Navigate to your case's constant/ directory and create a file named afcProperties:


Plaintext
/*--------------------------------*- C++ -*----------------------------------*\
| =========                 |                                                 |
| \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox           |
|  \\    /   O peration     | Version:  2312                                  |
|   \\  /    A nd           | Website:  [www.openfoam.com](https://www.openfoam.com)                      |
|    \\/     M anipulation  |                                                 |
\*---------------------------------------------------------------------------*/

FoamFile
{
    version     2.0;
    format      ascii;
    class       dictionary;
    object      afcProperties;
}
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// Acceleration of the jet pulse

jetAmplitude    [0 1 -2 0 0 0 0] 50.0;

// Frequency of the pulse (Hz)

jetFrequency    [0 0 -1 0 0 0 0] 10.0;

// Orientation of the jet (X, Y, Z)

jetDirection    [0 0 0 0 0 0 0] (0 1 0); 

Update your system/controlDict to use the new solver:

Plaintext
application     stealthAfcFoam;

Run the case:


stealthAfcFoam

👨‍💻 Author
Suyash Gupta
Mechanical Engineering | Computational Fluid Dynamics (CFD)
