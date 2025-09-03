/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | www.openfoam.com
     \\/     M anipulation  |
-------------------------------------------------------------------------------
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

Description
    Template for use with codeStream.

\*---------------------------------------------------------------------------*/

#include "dictionary.H"
#include "Ostream.H"
#include "Pstream.H"
#include "pointField.H"
#include "tensor.H"
#include "unitConversion.H"

//{{{ begin codeInclude
#line 24 "/home/user/OpenFOAM/user-v2412/applications/solvers/twoComponentLiquidFoam/cases/bubbleColumn/0/U/#codeStream"
#include "fvCFD.H"
//}}} end codeInclude

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

// * * * * * * * * * * * * * * * Local Functions * * * * * * * * * * * * * * //

//{{{ begin localCode

//}}} end localCode


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

extern "C" void codeStream_af630dc49aa009d98015bbbf16500a1daa45be84(Foam::Ostream& os, const Foam::dictionary& dict)
{
//{{{ begin code
    #line 41 "/home/user/OpenFOAM/user-v2412/applications/solvers/twoComponentLiquidFoam/cases/bubbleColumn/0/U/#codeStream"
/* Access to internal mesh information */
    const IOdictionary& d = static_cast<const IOdictionary&>(dict);
    const fvMesh& mesh = refCast<const fvMesh>(d.db());

    vectorField U(mesh.nCells()); /* initialization */

    /* User variables initialization */
    const scalar U0 = 0.2;          // амплитуда a
    const scalar L = 0.15;          // длина L


    forAll(U, i) /* Loop on elements */
    {
      const scalar x = mesh.C()[i][0]; /* Access to z component of cell centers coordinates */
      U[i].y() = U0 * (1 - ((x - (L/2)) / (L/2)) * ((x - (L/2)) / (L/2)));
    }

    U.writeEntry("", os); /* Write output in the dictionary */
//}}} end code
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// ************************************************************************* //

