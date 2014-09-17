#include "ZeroMB.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsCoreParams.hpp"

ZeroMB::ZeroMB(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams) : GradELA(aComponent, aPhysCoreParams)
{
	// TODO: assert that aComponent doesn't contain anything!
	_parameters.emplace("m1", 0);
	_parameters.emplace("m2", 0);
	_parameters.emplace("ELA", 0);
	_parameters.emplace("eps", 0);
}

ZeroMB::~ZeroMB() 
{ 

}
