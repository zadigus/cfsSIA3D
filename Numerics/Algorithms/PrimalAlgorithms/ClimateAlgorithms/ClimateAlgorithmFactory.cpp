#include "ClimateAlgorithmFactory.hpp"
#include "Utility/Logger/Logger.hpp"
#include "FullyImplicitClimateAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	PrimalAlgorithm* ClimateAlgorithmFactory::make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo)
	{
		if (aClimateAlgo)
		{
			if (aClimateAlgo->type().present())
			{
				if (!std::strcmp(aClimateAlgo->type()->c_str(), "FullyImplicit"))
				{
					LOG_INF("Setting FullyImplicit climate algorithm.");
					return new FullyImplicitClimateAlgorithm(aNumCoreParams, aClimateAlgo); 
				}
			}
			else // no ClimateAlgo type provided => default algo
			{
				LOG_ERR("Climate algorithm type not provided.");
				return new DumbAlgorithm();
			}
		}
		else // ClimateAlgo component not provided => default algo
		{
			LOG_ERR("Climate algorithm not provided.");
			return new DumbAlgorithm();
		}
	}

}