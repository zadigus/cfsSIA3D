#include "DiffusionAlgorithmFactory.hpp"

#include "SemiImplicitDiffusionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* DiffusionAlgorithmFactory::make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo)
	{
		if (aDiffusionAlgo)
		{
			if (aDiffusionAlgo->type().present())
			{
				if (!std::strcmp(aDiffusionAlgo->type()->c_str(), "SemiImplicit"))
				{
					return new SemiImplicitDiffusionAlgorithm(aNumCoreParams, aDiffusionAlgo);
				}
			}
			else // no DiffusionAlgo type provided => default algo
			{
				std::cerr << "Diffusion algorithm type not provided." << std::endl; // TODO: log that
				return new DumbAlgorithm();
			}
		}
		else // DiffusionAlgo component not provided => default algo
		{
			std::cerr << "Diffusion algorithm not provided." << std::endl; // TODO: log that
			return new DumbAlgorithm();
		}
	}

}