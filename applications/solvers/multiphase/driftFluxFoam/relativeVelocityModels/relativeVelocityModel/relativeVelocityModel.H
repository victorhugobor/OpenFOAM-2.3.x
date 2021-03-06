/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright (C) 2014 OpenFOAM Foundation
     \\/     M anipulation  |
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

Class
    Foam::relativeVelocityModel

Description

SourceFiles
    relativeVelocityModel.C

\*---------------------------------------------------------------------------*/

#ifndef relativeVelocityModel_H
#define relativeVelocityModel_H

#include "fvCFD.H"
#include "dictionary.H"
#include "incompressibleTwoPhaseMixture.H"
#include "runTimeSelectionTables.H"

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace Foam
{

/*---------------------------------------------------------------------------*\
                         Class relativeVelocityModel Declaration
\*---------------------------------------------------------------------------*/

class relativeVelocityModel
{
    // Private Member Functions

        //- Disallow default bitwise copy construct
        relativeVelocityModel(const relativeVelocityModel&);

        //- Disallow default bitwise assignment
        void operator=(const relativeVelocityModel&);

protected:

    // Protected data

        //- Mixture properties
        const incompressibleTwoPhaseMixture& mixture_;

        //- Name of the continuous phase
        const word continuousPhaseName_;

        //- Continuous phase fraction
        const volScalarField& alphaC_;

        //- Dispersed phase fraction
        const volScalarField& alphaD_;

        //- Continuous density
        const dimensionedScalar& rhoC_;

        //- Dispersed density
        const dimensionedScalar& rhoD_;

        //- Dispersed diffusion velocity
        volVectorField Udm_;

        //- Stress
        volSymmTensorField tau_;


public:

    //- Runtime type information
    TypeName("relativeVelocityModel");

    //- Declare runtime constructor selection table
    declareRunTimeSelectionTable
    (
        autoPtr,
        relativeVelocityModel,
        dictionary,
        (const dictionary& dict, const incompressibleTwoPhaseMixture& mixture),
        (dict, mixture)
    );


    // Constructors

        //- Construct from components
        relativeVelocityModel
        (
            const dictionary& dict,
            const incompressibleTwoPhaseMixture& mixture
        );


    // Selector
    static autoPtr<relativeVelocityModel> New
    (
        const dictionary& dict,
        const incompressibleTwoPhaseMixture& mixture
    );


    //- Destructor
    virtual ~relativeVelocityModel();


    // Member Functions

        //- Calculate the relative velocity of the dispersed phase
        virtual tmp<volVectorField> Ur() const = 0;

        //- Return the diffusion velocity of the dispersed phase
        const volVectorField& Udm() const
        {
            return Udm_;
        }

        //- Return the stress tensor due to the phase transport
        const volSymmTensorField& tau() const
        {
            return tau_;
        }

        //- Update the stored diffusion velocity and stress
        void update();
};


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace Foam

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#endif

// ************************************************************************* //
