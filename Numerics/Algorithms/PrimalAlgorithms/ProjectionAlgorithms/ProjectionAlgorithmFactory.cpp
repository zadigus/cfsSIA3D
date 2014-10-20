#include "ProjectionAlgorithmFactory.hpp"

#include "HeavisideProjectionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* ProjectionAlgorithmFactory::make(N_Configuration::Component* aProjectionAlgo)
	{
		if (aProjectionAlgo)
		{
			if (aProjectionAlgo->type().present())
			{
				if (!std::strcmp(aProjectionAlgo->type()->c_str(), "Heaviside"))
				{
					return new HeavisideProjectionAlgorithm(aProjectionAlgo);
				}
			}
			else // no ProjctionAlgo type provided => default algo
			{
				std::cerr << "Projection algorithm type not provided." << std::endl;
				return new DumbAlgorithm();
			}
		}
		else // ProjectionAlgo component not provided => default algo
		{
			std::cerr << "Projection algorithm type not provided." << std::endl;
			return new DumbAlgorithm();
		}
	}

}