#include "AltitudeSL.hpp"

#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsConfiguration.hpp"

namespace N_Physics {

	AltitudeSL::AltitudeSL(Component* aComponent) 
		: SlidingLaw(aComponent)
		, _Z(std::stod(_parameters["Z"]))
		, _C(std::stod(_parameters["C"]))
	{

	}

	AltitudeSL::AltitudeSL() : SlidingLaw()
	{

	}

	AltitudeSL::~AltitudeSL()
	{

	}

	void AltitudeSL::Fill(Grid& bed, unsigned int n)
	{
		assert(C() >= 0);
		if (C() > 0) {
			for (unsigned int i = 0; i < bed.Nx(); i++)
			{
				for (unsigned int j = 0; j<bed.Ny(); j++)
				{
					(*_sc)(i, j) = 0;
					if (Z() - bed(i, j) > 0)
						(*_sc)(i, j) = C() * pow(Z() - bed(i, j), 1. / n); // sliding at the grid points
				}
			}
		}
	}

}