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


// Функция для вычисления средней скорости на выходном патче
void calculateAverageOutletVelocity(const Time& runTime, const fvMesh& mesh)
{
    // Имя выходного патча (замените на ваше)
    const word outletPatchName = "outlet";

    // Проверка, существует ли патч
    if (!mesh.boundaryMesh().findPatchID(outletPatchName))
    {
        Info << "Patch " << outletPatchName << " not found!" << endl;
        return;
    }

    // Получение ID патча
    label outletPatchID = mesh.boundaryMesh().findPatchID(outletPatchName);

    // Получение скорости на патче
    const volVectorField& U = mesh.lookupObject<volVectorField>("U");
    const vectorField& Up = U.boundaryField()[outletPatchID];

    // Получение площадей граней патча
    const scalarField& areas = mesh.boundary()[outletPatchID].magSf();

    // Вычисление средней скорости (взвешенной по площади)
    scalar sumAreas = gSum(areas);
    vector sumU = gSum(Up * areas);
    vector averageU = sumU / sumAreas;

    // Вывод результата
    Info << "Time = " << runTime.timeName() << ", Average outlet velocity = "
         << averageU << " m/s" << endl;
}


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



    while (runTime.run())
    {
        #include "readTimeControls.H"
        #include "compressibleCourantNo.H"
        #include "setDeltaT.H"

        ++runTime;

        Info<< "Time = " << runTime.timeName() << nl << endl;

        // --- Pressure-velocity PIMPLE corrector loop

        while (pimple.loop())
        {
            U.storePrevIter();
            rho.storePrevIter();
            phi.storePrevIter();
            phiByRho.storePrevIter();
            p.storePrevIter();

            #include "UEqn.H"
            #include "rhoEqn_m.H"

            // --- Pressure corrector loop
            while (pimple.correct())
            {
                #include "pEqn.H"
            }

        }

        runTime.write();
        if (runTime.outputTime())
        {
            p.write(); 
        }

        // calculateAverageOutletVelocity(runTime, mesh);

        runTime.printExecutionTime(Info);
    }

    Info<< "End\n" << endl;

    return 0;
}


// ************************************************************************* //
