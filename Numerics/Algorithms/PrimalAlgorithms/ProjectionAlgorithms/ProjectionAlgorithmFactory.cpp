#include "ProjectionAlgorithmFactory.hpp"
#include "Utility/Logger/Logger.hpp"
#include "HeavisideProjectionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	PrimalAlgorithm* ProjectionAlgorithmFactory::make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo)
	{
		if (aProjectionAlgo)
		{
			if (aProjectionAlgo->type().present())
			{
				if (!std::strcmp(aProjectionAlgo->type()->c_str(), "Heaviside"))
				{
					LOG_INF("Setting 'Heaviside' projection algorithm.");
					return new HeavisideProjectionAlgorithm(aNumCoreParams, aProjectionAlgo);
				}
			}
			else // no ProjctionAlgo type provided => default algo
			{
				LOG_ERR("Projection algorithm type not provided.");
				return new DumbAlgorithm();
			}
		}
		else // ProjectionAlgo component not provided => default algo
		{
			LOG_ERR("Projection algorithm type not provided.");
			return new DumbAlgorithm();
		}
	}

}