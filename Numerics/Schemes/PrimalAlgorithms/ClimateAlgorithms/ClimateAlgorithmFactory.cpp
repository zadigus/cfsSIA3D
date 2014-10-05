#include "ClimateAlgorithmFactory.hpp"

#include "FullyImplicitClimateAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* ClimateAlgorithmFactory::make(const std::shared_ptr<Grid>& H, N_Configuration::Component* aClimateAlgo)
	{
		if (aClimateAlgo)
		{
			if (aClimateAlgo->type().present())
			{
				if (!std::strcmp(aClimateAlgo->type().c_str(), "FullyImplicit"))
				{
					return new FullyImplicitClimateAlgorithm(aClimateAlgo, H);
				}
			}
			else // no ClimateAlgo type provided => default algo
			{
				std::cerr << "Climate algorithm type not provided." << std::endl;
				return new DumbAlgorithm(H);
			}
		}
		else // ClimateAlgo component not provided => default algo
		{
			std::cerr << "Climate algorithm not provided." << std::endl;
			return new DumbAlgorithm(H);
		}
	}

}