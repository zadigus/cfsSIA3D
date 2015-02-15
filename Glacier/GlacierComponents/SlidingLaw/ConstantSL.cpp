#include "ConstantSL.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	ConstantSL::ConstantSL(const N_Configuration::Component& a_Component)
		: SlidingLaw(a_Component)
	{
		LOG_INF("Grid file name " << m_Parameters.at("grid"));
	}

	ConstantSL::~ConstantSL()
	{

	}

	void ConstantSL::Init(const std::shared_ptr<Geometry> &a_Geometry)
	{
		m_sc.reset(new Grid(m_Parameters.at("grid"))); 
		m_sl.reset(new Grid(m_sc->Nx(), m_sc->Ny(), m_sc->Dx(), m_sc->Dy()));
	}

	void ConstantSL::Fill(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp)
	{

	}

}
