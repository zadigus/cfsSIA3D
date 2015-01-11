#include "AltitudeSL.hpp"
#include "Utility/Logger/Logger.hpp"
#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	AltitudeSL::AltitudeSL(const N_Configuration::Component& aComponent)
		: SlidingLaw(aComponent)
		//, m_Z(m_Parameters.find("Z") != m_Parameters.end() ? std::stod(m_Parameters["Z"]) : 0)
		//, m_C(m_Parameters.find("C") != m_Parameters.end() ? std::stod(m_Parameters["C"]) : 0)
		, m_Z(std::stod(m_Parameters.at("Z")))
		, m_C(std::stod(m_Parameters.at("C")))
	{
		LOG_INF("Z = " << Z());
		LOG_INF("C = " << C());
	}
	
	AltitudeSL::AltitudeSL()
		: SlidingLaw()
		, m_Z(0)
		, m_C(0)
	{
		LOG_INF("Z = " << Z());
		LOG_INF("C = " << C());
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