#include "ClimateAlgorithmFactory.hpp"

#include "FullyImplicitClimateAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

//#include "Numerics/Mesh/Grid.hpp"
//#include "Glacier/Glacier.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* ClimateAlgorithmFactory::make(N_Configuration::Component* aClimateAlgo)
	{
		if (aClimateAlgo)
		{
			if (aClimateAlgo->type().present())
			{
				if (!std::strcmp(aClimateAlgo->type()->c_str(), "FullyImplicit"))
				{
					return new FullyImplicitClimateAlgorithm(aClimateAlgo); 
				}
			}
			else // no ClimateAlgo type provided => default algo
			{
				std::cerr << "Climate algorithm type not provided." << std::endl;
				return new DumbAlgorithm();
			}
		}
		else // ClimateAlgo component not provided => default algo
		{
			std::cerr << "Climate algorithm not provided." << std::endl;
			return new DumbAlgorithm();
		}
	}

}