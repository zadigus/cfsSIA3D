#include "ConstantSL.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	ConstantSL::ConstantSL(N_Configuration::Component* aComponent)
		: SlidingLaw(aComponent)
	{
		LOG_INF("Grid file name " << m_parameters["grid"]);
	}

	ConstantSL::~ConstantSL()
	{

	}

	void ConstantSL::Init(const Grid& bed)
	{
		m_sc.reset(new Grid(m_parameters["grid"])); 
		m_sl.reset(new Grid(m_sc->Nx(), m_sc->Ny(), m_sc->Dx(), m_sc->Dy()));
	}
}