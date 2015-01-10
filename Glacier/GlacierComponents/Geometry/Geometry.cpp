#include "Geometry.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier {

	//Geometry::Geometry(N_Configuration::Component* aComponent)
	Geometry::Geometry(const N_Configuration::Component& aComponent)
		: GlacierComponent(aComponent)
		, m_b(new Grid(m_parameters["bed"]))
		, m_gradbx(new Grid(m_b->Nx(), m_b->Ny(), m_b->Dx(), m_b->Dy(), m_b->Xll(), m_b->Yll()))
		, m_gradby(new Grid(*m_gradbx))
	{
		Grid s(m_parameters["surface"]);
		m_H.reset(new Grid(s-*m_b));
		
		for (unsigned int i(1); i < m_b->Nx(); ++i) 
		{
			for (unsigned int j(1); j < m_b->Ny(); ++j) 
			{
				(*m_gradbx)(i, j) = ((*m_b)(i, j) - (*m_b)(i - 1, j)) / m_b->Dx(); 
				(*m_gradby)(i, j) = ((*m_b)(i, j) - (*m_b)(i, j - 1)) / m_b->Dx(); 
			}
		}
	}

	Geometry::~Geometry() 
	{
	
	}
	
}