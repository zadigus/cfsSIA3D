#include "ConstantSL.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	ConstantSL::ConstantSL(N_Configuration::Component* aComponent)
		: SlidingLaw(aComponent)
	{
		
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