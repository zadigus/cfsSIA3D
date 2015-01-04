#include "SlidingLaw.hpp"

#include <cmath>
#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Glacier {

	SlidingLaw::SlidingLaw(N_Configuration::Component* aSlidingLaw)
		: GlacierComponent(aSlidingLaw)
		, m_sl(nullptr)
		, m_sc(nullptr)
	{

	}

	SlidingLaw::~SlidingLaw()
	{

	}

	void SlidingLaw::Generate(const Grid& fs, double n)
	{
		Init(fs);
		Fill(fs, n);
		Stagger(n);
	}

	void SlidingLaw::Init(const Grid& bed)
	{
		m_sl.reset(new Grid(bed.Nx(), bed.Ny(), bed.Dx(), bed.Dy()));
		m_sc.reset(new Grid(bed.Nx(), bed.Ny(), bed.Dx(), bed.Dy()));
	}

	void SlidingLaw::Fill(const Grid& bed, double n)
	{

	}

	void SlidingLaw::Stagger(double n)
	{ // n is Glen's exponent
		for (unsigned int i = 1; i < m_sl->Nx(); ++i)
			for (unsigned int j = 1; j < m_sl->Ny(); ++j) // convert to consistent units and project onto staggered grid
				(*m_sl)(i, j) = (pow((*m_sc)(i, j)*1e-5, n) + pow((*m_sc)(i - 1, j)*1e-5, n) + pow((*m_sc)(i, j - 1)*1e-5, n) + pow((*m_sc)(i - 1, j - 1)*1e-5, n)) / 4.;
	}

	// Access to class members
	const double& SlidingLaw::operator()(const unsigned int i, const unsigned int j) const
	{
		// access to staggered grid
		return (*m_sl)(i, j);
	}

	void SlidingLaw::Export(std::string fileName) const
	{
		m_sc->Export(fileName);
	}

	void SlidingLaw::ExportSL(std::string fileName) const
	{
		m_sl->Export(fileName);
	}

}