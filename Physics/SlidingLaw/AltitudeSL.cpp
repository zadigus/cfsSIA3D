#include "AltitudeSL.hpp"

#include <cassert>
#include <cmath>
#include "Grid.hpp"

AltitudeSL::AltitudeSL(std::string slFile, Grid& b, int n) : SlidingLaw(b.Nx(), b.Ny(), b.Dx())
{
	_x.resize(2);
	ReadModelParameters(slFile, _x, 2);
	Generate(b, n);
}

AltitudeSL::AltitudeSL(Grid& b, double Z, double C, int n) : SlidingLaw(b.Nx(), b.Ny(), b.Dx())
{
	_x.resize(2);
	_x[0] = Z; _x[1] = C;
	Generate(b, n);
}

AltitudeSL::~AltitudeSL()
{

}

void AltitudeSL::Generate(Grid& b, int n)
{ // the sliding coefficient depends on the bedrock topography, hence this
	// routine has to be called whenever the bedrock changes
	assert(C() >= 0);
	if(C() > 0) {
		for(unsigned int i=0; i<_sc->Nx(); i++) 
		{
			for(unsigned int j=0; j<_sc->Ny(); j++) 
			{
				(*_sc)(i, j) = 0;
				if(Z()-b(i, j) > 0)
					(*_sc)(i, j) = C() * pow(Z()-b(i, j), 1./n); // sliding at the grid points
			}
		}
	}
	Stagger(n); // generate sliding at the staggered grid's points
}
