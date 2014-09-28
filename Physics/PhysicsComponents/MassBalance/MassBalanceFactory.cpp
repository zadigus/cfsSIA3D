#include "MassBalanceFactory.hpp"

#include "AcAmELA.hpp"
#include "GradELA.hpp"
#include "ZeroMB.hpp"
#include "ConstantMB.hpp"

#include "PhysicsConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

#include <iostream>

namespace N_Physics {

	MassBalance* MassBalanceFactory::make(Component* aMassBalance, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
	{ // TODO: print a notification about the chosen massbalance type; add general PhysicalComponent::_name and print() members like with packages
		if (aMassBalance && aPhysCoreParams)
		{
			if (aMassBalance->type().present())
			{
				if (aMassBalance->type()->compare("AcAmELA"))
					return new AcAmELA(aMassBalance, aPhysCoreParams);
				else if (aMassBalance->type()->compare("GradELA"))
					return new GradELA(aMassBalance, aPhysCoreParams);
				else if (aMassBalance->type()->compare("Constant"))
					return new ConstantMB(aMassBalance, aPhysCoreParams);
				else
				{
					std::cout << "Unknown type " << aMassBalance->type() << ". Setting MassBalance to zero." << std::endl;
					return new ZeroMB(/*aMassBalance, aPhysCoreParams*/); // if unknown, then set B = 0
				}
			}
			else
			{
				std::cout << "Type not specified. Setting MassBalance to zero." << std::endl;
				return new ZeroMB(/*aMassBalance, aPhysCoreParams*/); // if type not set, then set B = 0
			}
		}
		else
		{
			std::cout << "No configuration provided. Setting MassBalance to zero." << std::endl;
			return new ZeroMB();
		}
	}

}