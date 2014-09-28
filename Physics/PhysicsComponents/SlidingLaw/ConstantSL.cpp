#include "ConstantSL.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsConfiguration.hpp"

namespace N_Physics {

	ConstantSL::ConstantSL(Component* aComponent)
		: SlidingLaw(aComponent)
	{
		// nothing to be differentiated, hence no initialization of _x!
		//_sc.reset(new Grid(fileName));
		//_sl.reset(new Grid(_sc->Nx(), _sc->Ny(), _sc->Dx()));
		//Stagger(n);
	}

	ConstantSL::~ConstantSL()
	{

	}

	void ConstantSL::Init(const Grid& bed)
	{
		_sc.reset(new Grid(_parameters["grid"])); // TODO: deal with this problem; the _parameter is of type double; we want also string parameters; OR do only string parameters and then cast
		_sl.reset(new Grid(_sc->Nx(), _sc->Ny(), _sc->Dx(), _sc->Dy()));
	}

	/*void ConstantSL::Fill(Grid& fs, int n)
	{
	//Stagger(n);
	}*/

}