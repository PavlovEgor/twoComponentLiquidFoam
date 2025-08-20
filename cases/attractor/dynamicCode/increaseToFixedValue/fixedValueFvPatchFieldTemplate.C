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
// SHA1 = 5a8b32bcf1c7e883416a51f6af380d0c030d885b
//
// unique function name that can be checked if the correct library version
// has been loaded
extern "C" void increaseToFixedValue_5a8b32bcf1c7e883416a51f6af380d0c030d885b(bool load)
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
    increaseToFixedValueFixedValueFvPatchVectorField
);

} // End namespace Foam


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
increaseToFixedValueFixedValueFvPatchVectorField
(
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(p, iF)
{
    if (false)
    {
        printMessage("Construct increaseToFixedValue : patch/DimensionedField");
    }
}


Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
increaseToFixedValueFixedValueFvPatchVectorField
(
    const increaseToFixedValueFixedValueFvPatchVectorField& rhs,
    const fvPatch& p,
    const DimensionedField<vector, volMesh>& iF,
    const fvPatchFieldMapper& mapper
)
:
    parent_bctype(rhs, p, iF, mapper)
{
    if (false)
    {
        printMessage("Construct increaseToFixedValue : patch/DimensionedField/mapper");
    }
}


Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
increaseToFixedValueFixedValueFvPatchVectorField
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
        printMessage("Construct increaseToFixedValue : patch/dictionary");
    }
}


Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
increaseToFixedValueFixedValueFvPatchVectorField
(
    const increaseToFixedValueFixedValueFvPatchVectorField& rhs
)
:
    parent_bctype(rhs),
    dictionaryContent(rhs)
{
    if (false)
    {
        printMessage("Copy construct increaseToFixedValue");
    }
}


Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
increaseToFixedValueFixedValueFvPatchVectorField
(
    const increaseToFixedValueFixedValueFvPatchVectorField& rhs,
    const DimensionedField<vector, volMesh>& iF
)
:
    parent_bctype(rhs, iF)
{
    if (false)
    {
        printMessage("Construct increaseToFixedValue : copy/DimensionedField");
    }
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

Foam::
increaseToFixedValueFixedValueFvPatchVectorField::
~increaseToFixedValueFixedValueFvPatchVectorField()
{
    if (false)
    {
        printMessage("Destroy increaseToFixedValue");
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void
Foam::
increaseToFixedValueFixedValueFvPatchVectorField::updateCoeffs()
{
    if (this->updated())
    {
        return;
    }

    if (false)
    {
        printMessage("updateCoeffs increaseToFixedValue");
    }

//{{{ begin code
    #line 72 "/home/user/OpenFOAM/user-v2412/applications/solvers/MyrhoPimpleAdiabaticFoam/cases/attractor/0/U/boundaryField/left"
const vectorField& Cf = patch().Cf();
               vectorField& field    = *this;
               const scalar a0 = 0.11* 0.001;
               const scalar w0 = 0.628;
               const scalar H  = 0.4;
               const scalar pi = constant::mathematical::pi;
									             
               forAll(Cf, faceI)
               {
                   const scalar y = Cf[faceI][1];
                   const scalar t = this->db().time().value();
                   field[faceI]   = vector(a0*w0*sin(2*pi*y/H)*cos(w0*t),0,0);
               }
//}}} end code

    this->parent_bctype::updateCoeffs();
}


// ************************************************************************* //

