/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2017 OpenCFD Ltd.
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

Application
    rhoPimpleAdiabaticFoam

Description
    Transient solver for laminar or turbulent flow of weakly compressible
    fluids for low Mach number aeroacoustic applications.

    Uses the flexible PIMPLE (PISO-SIMPLE) solution for time-resolved and
    pseudo-transient simulations. The RCM interpolation is used as in

    \verbatim
        Knacke, T. (2013).
        Potential effects of Rhie & Chow type interpolations in airframe
        noise simulations. In: Schram, C., Dénos, R., Lecomte E. (ed):
        Accurate and efficient aeroacoustic prediction approaches for
        airframe noise, VKI LS 2013-03.
    \endverbatim

    Contact:      info@upstream-cfd.com

\*---------------------------------------------------------------------------*/

#include "fvCFD.H"
#include "fluidThermo.H"
#include "turbulentFluidThermoModel.H"
#include "bound.H"
#include "pimpleControl.H"
#include "fvOptions.H"

#include "ddtScheme.H"
#include "fvcCorrectAlpha.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

int main(int argc, char *argv[])
{
    argList::addNote
    (
        "Transient solver for laminar or turbulent flow"
        " of weakly compressible fluids for low Mach number"
        " aeroacoustic applications."
    );

    #include "postProcess.H"

    #include "addCheckCaseOptions.H"
    #include "setRootCaseLists.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createControl.H"
    #include "createTimeControls.H"

    #include "createFields.H"
    #include "createFvOptions.H"
    // #include "initContinuityErrs.H"

    // * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

    Info<< "\nStarting time loop\n" << endl;

    dimensionedScalar rho2("rho2", dimensionSet(1, -3, 0, 0, 0, 0, 0), 1.0);
    dimensionedScalar D("D", dimensionSet(0, 2, -1, 0, 0, 0, 0), 0.0000198);
    dimensionedScalar c2("c2", dimensionSet(0, -2, 2, 0, 0, 0, 0), 1.0/2190400);

    while (runTime.run())
    {
        #include "readTimeControls.H"
        #include "compressibleCourantNo.H"
        #include "setDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        if (pimple.nCorrPIMPLE() <= 1)
        {
            #include "rhoEqn.H"
        }

        // --- Pressure-velocity PIMPLE corrector loop
        while (pimple.loop())
        {
            U.storePrevIter();
            rho.storePrevIter();
            phi.storePrevIter();
            phiByRho.storePrevIter();

            
            #include "rhoEqn.H"
            #include "UEqn.H"

            
            for (int l = 0; l < 2; l++)
            {
                // Info<< "Time = before pEqn.h" << nl << endl;
                #include "rhoUEqn.H"
                #include "UEqn.H"
            }
            
            #include "contError.H"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
                // Info<< "Time = before pEqn.h" << nl << endl;
                #include "pEqn.H"
            }

            
            

            // if (pimple.turbCorr())
            // {
            //     turbulence->correct();
            // }
        }

        runTime.write();

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
