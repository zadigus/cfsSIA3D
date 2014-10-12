#include "AltitudeSL.hpp"

#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	AltitudeSL::AltitudeSL(N_Configuration::Component* aComponent)
		: SlidingLaw(aComponent)
		, _Z(_parameters.find("Z") != _parameters.end() ? std::stod(_parameters["Z"]) : 0)
		, _C(_parameters.find("C") != _parameters.end() ? std::stod(_parameters["C"]) : 0)
	{
		
	}

	/*AltitudeSL::AltitudeSL() : SlidingLaw()
	{

	}*/

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