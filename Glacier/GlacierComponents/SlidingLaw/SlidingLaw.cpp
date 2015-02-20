#include "SlidingLaw.hpp"

#include <cmath>
#include "Numerics/Mesh/Grid.hpp"
#include "Epetra_Vector.h"
#include "Geometry/Geometry.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	SlidingLaw::SlidingLaw(const N_Configuration::Component& a_SlidingLaw)
		: GlacierComponent(a_SlidingLaw)
		, m_sl(nullptr)
		, m_sc(nullptr)
	{

	}

	SlidingLaw::SlidingLaw()
		: GlacierComponent()
		, m_sl(nullptr)
		, m_sc(nullptr)
	{

	}

	SlidingLaw::~SlidingLaw()
	{

	}

	void SlidingLaw::Generate(const std::shared_ptr<Geometry> &a_Geometry, double a_GlenExp)
	{
		Init(a_Geometry);
		Fill(a_Geometry, a_GlenExp);
		Stagger(a_GlenExp);
	}

	void SlidingLaw::Init(const std::shared_ptr<Geometry>& a_Geometry)
	{
		m_sl.reset(new Grid(a_Geometry->Nx(), a_Geometry->Ny(), a_Geometry->Dx(), a_Geometry->Dy()));
		m_sc.reset(new Grid(a_Geometry->Nx(), a_Geometry->Ny(), a_Geometry->Dx(), a_Geometry->Dy()));
	}

	void SlidingLaw::Stagger(double a_GlenExp)
	{
		double OnePaToBar(1e-5), convCoeff(pow(OnePaToBar, a_GlenExp));
    for (size_t i = 1; i < m_sl->Nx(); ++i)
      for (size_t j = 1; j < m_sl->Ny(); ++j) // convert to consistent units and project onto staggered grid
				(*m_sl)(i, j) = convCoeff/4 *(		pow((*m_sc)(i  ,   j), a_GlenExp)
																				+ pow((*m_sc)(i-1,   j), a_GlenExp)
																				+ pow((*m_sc)(i  , j-1), a_GlenExp)
																				+ pow((*m_sc)(i-1, j-1), a_GlenExp)
																		 );
	}

	// Access to class members
  const double& SlidingLaw::operator()(size_t i, size_t j) const
	{
		// access to staggered grid
		return (*m_sl)(i, j);
	}

  void SlidingLaw::Export(std::string fileName) const
	{
    toGrid(*m_sc, fileName);
	}

	void SlidingLaw::ExportSL(std::string fileName) const
	{
    toGrid(*m_sl, fileName);
	}

}
