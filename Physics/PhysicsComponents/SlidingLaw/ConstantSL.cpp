#include "ConstantSL.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsConfiguration.hpp"

namespace N_Physics {

	ConstantSL::ConstantSL(Component* aComponent)
		: SlidingLaw(aComponent)
	{
		
	}

	ConstantSL::~ConstantSL()
	{

	}

	void ConstantSL::Init(const Grid& bed)
	{
		_sc.reset(new Grid(_parameters["grid"])); 
		_sl.reset(new Grid(_sc->Nx(), _sc->Ny(), _sc->Dx(), _sc->Dy()));
	}
}