#include "MassBalanceFactory.hpp"
#include "Utility/Logger/Logger.hpp"

#include "AcAmELA.hpp"
#include "GradELA.hpp"
#include "ZeroMB.hpp"
#include "ConstantMB.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"


namespace N_Glacier {

	MassBalance* MassBalanceFactory::make(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aMassBalance)
	{ 
		if (aMassBalance && aPhysCoreParams)
		{
			if (aMassBalance->type().present())
			{
				if (!std::strcmp(aMassBalance->type()->c_str(), "AcAmELA")) {
					LOG_INF("Setting MassBalance AcAmELA");
					return new AcAmELA(aPhysCoreParams, aMassBalance);
				}
				else if (!std::strcmp(aMassBalance->type()->c_str(), "GradELA")) {
					LOG_INF("Setting MassBalance GradELA");
					return new GradELA(aPhysCoreParams, aMassBalance);
				}
				else if (!std::strcmp(aMassBalance->type()->c_str(), "Constant"))
				{
					LOG_INF("Setting MassBalance Constant");
					return new ConstantMB(aPhysCoreParams, aMassBalance);
				}
				else
				{
					LOG_WRN("Unknown type " << aMassBalance->type() << ". Setting MassBalance to zero.");
					return new ZeroMB(aPhysCoreParams); // if unknown, then set B = 0
				}
			}
			else
			{
				LOG_WRN("Type not specified. Setting MassBalance to zero.");
				return new ZeroMB(aPhysCoreParams); // if type not set, then set B = 0
			}
		}
		else
		{
			LOG_WRN("No configuration provided. Setting MassBalance to zero.");
			return new ZeroMB(aPhysCoreParams);
		}
	}

}