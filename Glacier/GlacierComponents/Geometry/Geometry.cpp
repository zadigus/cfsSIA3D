#include "Geometry.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier {
	Geometry::Geometry(const N_Configuration::Component& a_Component)
		: GlacierComponent(a_Component)
		, m_b(new Grid(m_Parameters["bed"]))
		, m_gradbx(new Grid(m_b->Nx(), m_b->Ny(), m_b->Dx(), m_b->Dy(), m_b->Xll(), m_b->Yll()))
		, m_gradby(new Grid(*m_gradbx))
	{
		Grid s(m_Parameters["surface"]);
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

	Geometry::Geometry(const Geometry& a_Geometry)
		: m_b(a_Geometry.m_b)
		, m_H(a_Geometry.m_H)
		, m_gradbx(a_Geometry.m_gradbx)
		, m_gradby(a_Geometry.m_gradby)
	{

	}

	Geometry& Geometry::operator=(const Geometry& a_Geometry)
	{
		m_b = a_Geometry.m_b;
		m_H = a_Geometry.m_H;
		m_gradbx = a_Geometry.m_gradbx;
		m_gradby = a_Geometry.m_gradby;
	}

	double Geometry::staggeredGradSurfNorm(unsigned int i, unsigned int j)
	{
		assert(m_H->Dx() == m_H->Dy());
		return sqrt((b(i, j    ) + H(i, j    ) - b(i - 1, j - 1) - H(i - 1, j - 1))*(b(i, j    ) + H(i, j    ) - b(i - 1, j - 1) - H(i - 1, j - 1))
							+ (b(i, j - 1) + H(i, j - 1) - b(i - 1, j    ) - H(i - 1, j    ))*(b(i, j - 1) + H(i, j - 1) - b(i - 1, j    ) - H(i - 1, j    ))
							 ) / (sqrt(2)*m_H->Dx());
	}

	unsigned int Geometry::Nx()
	{
		return m_H->Nx();
	}

	unsigned int Geometry::Ny()
	{
		return m_H->Ny();
	}

	double Geometry::Dx()
	{
		return m_H->Dx();
	}

	double Geometry::Dy()
	{
		return m_H->Dy();
	}

	double Geometry::b(unsigned int i, unsigned int j)
	{
		return (*m_b)(i, j);
	}

	double& Geometry::H(unsigned int i, unsigned int j)
	{
		return (*m_H)(i, j);
	}

	double Geometry::gradbx(unsigned int i, unsigned int j)
	{
		return (*m_gradbx)(i, j);
	}

	double Geometry::gradby(unsigned int i, unsigned int j)
	{
		return (*m_gradby)(i, j);
	}
}
