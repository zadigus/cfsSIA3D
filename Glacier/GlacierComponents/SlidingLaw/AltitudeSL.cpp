#include "AltitudeSL.hpp"

#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	AltitudeSL::AltitudeSL(N_Configuration::Component* aComponent)
		: SlidingLaw(aComponent)
		, m_Z(m_parameters.find("Z") != m_parameters.end() ? std::stod(m_parameters["Z"]) : 0)
		, m_C(m_parameters.find("C") != m_parameters.end() ? std::stod(m_parameters["C"]) : 0)
	{
		
	}
	
	AltitudeSL::~AltitudeSL()
	{

	}

	void AltitudeSL::Fill(Grid& bed, unsigned int n)
	{
		assert(C() >= 0);
		if (C() > 0) {
			for (unsigned int i = 0; i < bed.Nx(); ++i)
			{
				for (unsigned int j = 0; j<bed.Ny(); ++j)
				{
					(*m_sc)(i, j) = 0;
					if (Z() - bed(i, j) > 0)
						(*m_sc)(i, j) = C() * pow(Z() - bed(i, j), 1. / n); // sliding at the grid points
				}
			}
		}
	}

}