#include "ConstantMB.hpp"
#include "PhysicsConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsCoreParams.hpp"

ConstantMB::ConstantMB(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
: MassBalance(aComponent, aPhysCoreParams)
, _mb(new Grid(_parameters["grid"])) // TODO: deal with this problem; the _parameter is of type double; we want also string parameters; OR do only string parameters and then cast
{
	
}

ConstantMB::~ConstantMB() 
{ 

}

const double ConstantMB::operator()(const double x, const double y, const double b, const double H)
{
	// only depends on surface altitude
	return (*_mb)(x, y);
}

const double ConstantMB::operator()(const double b, const double H3, const double H2) 
{
	return water2ice(0); // TODO: write this right; it must be the value of B at the position (x, y)
}

double ConstantMB::dB(double b, double H3, double H2) 
{ 
	return 0;
}
