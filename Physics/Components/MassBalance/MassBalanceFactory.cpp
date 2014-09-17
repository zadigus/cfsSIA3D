#include "MassBalanceFactory.hpp"

#include "AcAmELA.hpp"
#include "GradELA.hpp"
#include "ZeroMB.hpp"
#include "ConstantMB.hpp"

#include "PhysicsConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

MassBalance* MassBalanceFactory::make(Component* aMassBalance, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
{ // TODO: print a notification about the chosen massbalance type; add general PhysicalComponent::_name and print() members like with packages
	if (aMassBalance->type().present())
	{
		if (aMassBalance->type()->c_str() == "AcAmELA")
			return new AcAmELA(aMassBalance, aPhysCoreParams);
		else if (aMassBalance->type()->c_str() == "GradELA")
			return new GradELA(aMassBalance, aPhysCoreParams);
		else if (aMassBalance->type()->c_str() == "Constant")
			return new ConstantMB(aMassBalance, aPhysCoreParams);
		else
			return new ZeroMB(aMassBalance, aPhysCoreParams); // if unknown, then set B = 0
	} 
	else
	{
		return new ZeroMB(aMassBalance, aPhysCoreParams); // if type not set, then set B = 0
	}
}