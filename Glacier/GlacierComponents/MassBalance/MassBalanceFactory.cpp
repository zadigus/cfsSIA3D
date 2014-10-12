#include "MassBalanceFactory.hpp"

#include "AcAmELA.hpp"
#include "GradELA.hpp"
#include "ZeroMB.hpp"
#include "ConstantMB.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

#include <iostream>

namespace N_Glacier {

	MassBalance* MassBalanceFactory::make(std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aMassBalance)
	{ // TODO: print a notification about the chosen massbalance type; add general PhysicalComponent::_name and print() members like with packages
		if (aMassBalance && aPhysCoreParams)
		{
			if (aMassBalance->type().present())
			{
				//if (aMassBalance->type()->compare("ACAMELA")) {
				if (!std::strcmp(aMassBalance->type()->c_str(), "AcAmELA")) {
					return new AcAmELA(aPhysCoreParams, aMassBalance);
				}
				//else if (aMassBalance->type()->compare("GRADELA")) {
				else if (!std::strcmp(aMassBalance->type()->c_str(), "GradELA")) {
					return new GradELA(aPhysCoreParams, aMassBalance);
				}
				//else if (aMassBalance->type()->compare("CONSTANT"))
				else if (!std::strcmp(aMassBalance->type()->c_str(), "Constant"))
					return new ConstantMB(aPhysCoreParams, aMassBalance);
				else
				{
					std::cout << "Unknown type " << aMassBalance->type() << ". Setting MassBalance to zero." << std::endl;
					return new ZeroMB(); // if unknown, then set B = 0
				}
			}
			else
			{
				std::cout << "Type not specified. Setting MassBalance to zero." << std::endl;
				return new ZeroMB(); // if type not set, then set B = 0
			}
		}
		else
		{
			std::cout << "No configuration provided. Setting MassBalance to zero." << std::endl;
			return new ZeroMB();
		}
	}

}