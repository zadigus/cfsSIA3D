#include "SlidingLaw.hpp"

#include <cmath>
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsConfiguration.hpp"

SlidingLaw::SlidingLaw(Component* aSlidingLaw/*, unsigned int nx, unsigned int ny, double dx*/) 
: PhysicalComponent(aSlidingLaw)
, _sl(nullptr)
, _sc(nullptr)
//, _sl(new Grid(nx, ny, dx, dx))
//, _sc(new Grid(nx, ny, dx, dx))
{

}

SlidingLaw::~SlidingLaw()
{

}

void SlidingLaw::Generate(Grid& fs, unsigned int n)
{
	Init(fs);
	Fill(fs, n);
	Stagger(n);
}

void SlidingLaw::Init(const Grid& bed)
{
	_sl.reset(new Grid(bed.Nx(), bed.Ny(), bed.Dx(), bed.Dy()));
	_sc.reset(new Grid(bed.Nx(), bed.Ny(), bed.Dx(), bed.Dy()));
}

void SlidingLaw::Fill(Grid& bed, unsigned int n)
{

}

void SlidingLaw::Stagger(unsigned int n)
{ // n is Glen's exponent
	for(unsigned int i=1; i<_sl->Nx(); i++)
		for(unsigned int j=1; j<_sl->Ny(); j++) // convert to consistent units and project onto staggered grid
			(*_sl)(i, j) = (pow((*_sc)(i, j)*1e-5, n)+pow((*_sc)(i-1, j)*1e-5, n)+pow((*_sc)(i, j-1)*1e-5, n)+pow((*_sc)(i-1, j-1)*1e-5, n))/4.;
}

// Access to class members
const double& SlidingLaw::operator()(const unsigned int i, const unsigned int j) const
{
	// access to staggered grid
	return (*_sl)(i, j);
}

void SlidingLaw::Export(std::string fileName) const
{ 
	_sc->Export(fileName); 
}

void SlidingLaw::ExportSL(std::string fileName) const 
{ 
	_sl->Export(fileName); 
}
