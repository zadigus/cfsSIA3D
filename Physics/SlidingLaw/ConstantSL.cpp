#include "ConstantSL.hpp"

#include "Grid.hpp"

ConstantSL::ConstantSL(std::string fileName, int n) : SlidingLaw()
{
	// nothing to be differentiated, hence no initialization of _x!
	_sc.reset(new Grid(fileName));
	_sl.reset(new Grid(_sc->Nx(), _sc->Ny(), _sc->Dx()));
	Stagger(n);
}

ConstantSL::~ConstantSL()
{

}

void ConstantSL::Generate(Grid& fs, int n)
{
	Stagger(n);
}
