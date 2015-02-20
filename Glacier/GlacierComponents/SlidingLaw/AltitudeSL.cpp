#include "AltitudeSL.hpp"
#include "Utility/Logger/Logger.hpp"
#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "Geometry/Geometry.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	AltitudeSL::AltitudeSL(const N_Configuration::Component& a_Component)
		: SlidingLaw(a_Component)
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

	void AltitudeSL::Fill(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp)
	{
		assert(C() >= 0);
		if (C() > 0) {
      for (size_t i(0); i < a_Geometry->Nx(); ++i)
			{
        for (size_t j(0); j < a_Geometry->Ny(); ++j)
				{
					if (Z() - a_Geometry->b(i, j) > 0)
						(*m_sc)(i, j) = C() * pow(Z() - a_Geometry->b(i, j), 1. / a_GlenExp); // sliding at the grid points
				}
			}
		}
	}

}
