#include "ZeroSL.hpp"

#include <cassert>
#include <cmath>

#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsConfiguration.hpp"

ZeroSL::ZeroSL(Component* aComponent) : AltitudeSL(aComponent)
{
	// TODO: assert that aComponent doesn't contain anything!
	_parameters.emplace("C", 0);
	_parameters.emplace("Z", 0);
}

ZeroSL::~ZeroSL()
{

}

void ZeroSL::Stagger(unsigned int n)
{

}
