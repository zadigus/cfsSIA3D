#include "Geometry.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Epetra_Vector.h"

#include <iostream>

using namespace std;

namespace N_Glacier {
	Geometry::Geometry(const N_Configuration::Component& a_Component)
		: GlacierComponent(a_Component)
		, m_b(new Grid(m_Parameters["bed"]))
		, m_gradbx(new Grid(m_b->Nx(), m_b->Ny(), m_b->Dx(), m_b->Dy(), m_b->Xll(), m_b->Yll()))
		, m_gradby(new Grid(*m_gradbx))
	{
		Grid s(m_Parameters["surface"]);
		m_H.reset(new Grid(s-*m_b));
		
    for (size_t i(1); i < m_b->Nx(); ++i)
		{
      for (size_t j(1); j < m_b->Ny(); ++j)
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

  void Geometry::setH(const shared_ptr<Grid>& a_H)
  {
    m_H = a_H;
  }

  size_t Geometry::Nx() const
	{
		return m_H->Nx();
	}

  size_t Geometry::Ny() const
	{
		return m_H->Ny();
	}

  double Geometry::Dx() const
	{
		return m_H->Dx();
	}

  double Geometry::Dy() const
	{
		return m_H->Dy();
	}

  double Geometry::b(size_t i, size_t j) const
	{
		return (*m_b)(i, j);
	}

  double& Geometry::H(size_t i, size_t j)
	{
		return (*m_H)(i, j);
	}

  double Geometry::H(size_t i, size_t j) const
  {
    return (*m_H)(i, j);
  }

  double Geometry::gradbx(size_t i, size_t j) const
	{
		return (*m_gradbx)(i, j);
	}

  double Geometry::gradby(size_t i, size_t j) const
	{
		return (*m_gradby)(i, j);
	}

  /*
   * Non-member methods
   */
  double staggeredGradSurfNorm(const Geometry& a_g, size_t i, size_t j)
  {
    assert(a_g.Dx() == a_g.Dy());
    return sqrt((a_g.b(i, j    ) + a_g.H(i, j    ) - a_g.b(i - 1, j - 1) - a_g.H(i - 1, j - 1))*(a_g.b(i, j    ) + a_g.H(i, j    ) - a_g.b(i - 1, j - 1) - a_g.H(i - 1, j - 1))
              + (a_g.b(i, j - 1) + a_g.H(i, j - 1) - a_g.b(i - 1, j    ) - a_g.H(i - 1, j    ))*(a_g.b(i, j - 1) + a_g.H(i, j - 1) - a_g.b(i - 1, j    ) - a_g.H(i - 1, j    ))
               ) / (sqrt(2)*a_g.Dx());
  }

  void setThickness(Geometry& a_g, const shared_ptr<Grid>& a_H)
  {
    a_g.setH(a_H);
  }

  void setThickness(Geometry& a_g, const Teuchos::RCP<Epetra_Vector>& a_Vector)
  {
    size_t I(0);
    for (size_t i(0); i < a_g.Nx(); ++i)   // by default, we go from 0 and end with Nx/Ny
    {
      for (size_t j(0); j < a_g.Ny(); ++j)
      {
        a_g.H(i, j) = (*a_Vector)[I++];
      }
    }
  }

}
