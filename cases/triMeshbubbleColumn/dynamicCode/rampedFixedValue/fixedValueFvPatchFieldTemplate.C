/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
    Copyright (C) 2019-2021 OpenCFD Ltd.
    Copyright (C) YEAR AUTHOR, AFFILIATION
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

\*---------------------------------------------------------------------------*/

#include "fixedValueFvPatchFieldTemplate.H"
#include "addToRunTimeSelectionTable.H"
#include "fvPatchFieldMapper.H"
#include "volFields.H"
#include "surfaceFields.H"
#include "unitConversion.H"
#include "PatchFunction1.H"

//{{{ begin codeInclude

//}}} end codeInclude


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

// dynamicCode:
// SHA1 = 14670a4d605a4f4deb32367ee792478f1ca5bf97
//
// unique function name that can be checked if the correct library version
// has been loaded
extern "C" void rampedFixedValue_14670a4d605a4f4deb32367ee792478f1ca5bf97(bool load)
{
    if (load)
    {
        // Code that can be explicitly executed after loading
    }
    else
    {
        // Code that can be explicitly executed before unloading
    }
}

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

makeRemovablePatchTypeField
(
    fvPatchVectorField,
    rampedFixedValueFixedValueFvPatchVectorField
);

} // End namespace Foam


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::
rampedFixedValueFixedValueFvPatchVectorField::
rampedFixedValueFixedValueFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(p, iF)
{
    if (false)
    {
        printMessage("Construct rampedFixedValue : patch/DimensionedField");
    }
}


Foam::
rampedFixedValueFixedValueFvPatchVectorField::
rampedFixedValueFixedValueFvPatchVectorField
(
    const rampedFixedValueFixedValueFvPatchVectorField& rhs,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    parent_bctype(rhs, p, iF, mapper)
{
    if (false)
    {
        printMessage("Construct rampedFixedValue : patch/DimensionedField/mapper");
    }
}


Foam::
rampedFixedValueFixedValueFvPatchVectorField::
rampedFixedValueFixedValueFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const dictionary& dict
)
:
    parent_bctype(p, iF, dict)
{
    if (false)
    {
        printMessage("Construct rampedFixedValue : patch/dictionary");
    }
}


Foam::
rampedFixedValueFixedValueFvPatchVectorField::
rampedFixedValueFixedValueFvPatchVectorField
(
    const rampedFixedValueFixedValueFvPatchVectorField& rhs
)
:
    parent_bctype(rhs),
    dictionaryContent(rhs)
{
    if (false)
    {
        printMessage("Copy construct rampedFixedValue");
    }
}


Foam::
rampedFixedValueFixedValueFvPatchVectorField::
rampedFixedValueFixedValueFvPatchVectorField
(
    const rampedFixedValueFixedValueFvPatchVectorField& rhs,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(rhs, iF)
{
    if (false)
    {
        printMessage("Construct rampedFixedValue : copy/DimensionedField");
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::
rampedFixedValueFixedValueFvPatchVectorField::
~rampedFixedValueFixedValueFvPatchVectorField()
{
    if (false)
    {
        printMessage("Destroy rampedFixedValue");
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void
Foam::
rampedFixedValueFixedValueFvPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    if (false)
    {
        printMessage("updateCoeffs rampedFixedValue");
    }

//{{{ begin code
    #line 82 "/home/user/OpenFOAM/user-v2412/applications/solvers/twoComponentLiquidFoam/cases/triMeshbubbleColumn/0/U/boundaryField/bottom"
// Параметры:
            const scalar U0 = 0.2;          // амплитуда a
            const scalar L = 0.15;          // длина L


            // Для каждой точки границы:
            const vectorField& faceCenters = patch().Cf();
            vectorField result(faceCenters.size(), vector::zero);

            forAll(faceCenters, faceI)
            {
                scalar x = faceCenters[faceI].x(); // координата x точки на границе
                result[faceI].y() = U0 * (1 - ((x - (L/2)) / (L/2)) * ((x - (L/2)) / (L/2)));
            }

            operator==(result);
//}}} end code

    this->parent_bctype::updateCoeffs();
}


// ************************************************************************* //

