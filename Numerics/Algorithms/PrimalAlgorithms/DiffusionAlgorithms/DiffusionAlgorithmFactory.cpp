#include "DiffusionAlgorithmFactory.hpp"
#include "Utility/Logger/Logger.hpp"
#include "SemiImplicitDiffusionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

namespace N_Mathematics {

	//PrimalAlgorithm* DiffusionAlgorithmFactory::make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo)
	PrimalAlgorithm* DiffusionAlgorithmFactory::make(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aDiffusionAlgo)
	{
		//if (aDiffusionAlgo)
		//{
			if (aDiffusionAlgo.type().present())
			{
				if (!std::strcmp(aDiffusionAlgo.type()->c_str(), "SemiImplicit"))
				{
					LOG_INF("Setting SemiImplicit diffusion algorithm.");
					SemiImplicitDiffusionAlgorithm* sa(new SemiImplicitDiffusionAlgorithm(aNumCoreParams, aDiffusionAlgo));
					sa->setCrs();
					return sa;
				}
			}
			else // no DiffusionAlgo type provided => default algo
			{
				LOG_WRN("Diffusion algorithm type not provided. Setting algorithm that does nothing.");
				return new DumbAlgorithm();
			}
		//}
		
		//// DiffusionAlgo component not provided => default algo
		//LOG_WRN("Diffusion algorithm not provided. Setting algorithm that does not nothing.");
		//return new DumbAlgorithm();
	}

	//PrimalAlgorithm* DiffusionAlgorithmFactory::make(const NumericsCoreParams& aNumCoreParams)
	//{
	//	// DiffusionAlgo component not provided => default algo
	//	LOG_WRN("Diffusion algorithm not provided. Setting algorithm that does not nothing.");
	//	return new DumbAlgorithm();
	//}

}