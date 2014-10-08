#include "ClimateAlgorithmFactory.hpp"

#include "FullyImplicitClimateAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

//#include "Numerics/Mesh/Grid.hpp"
//#include "Glacier/Glacier.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* ClimateAlgorithmFactory::make(/*std::shared_ptr<N_Glacier::Glacier>& aGlacier, */N_Configuration::Component* aClimateAlgo)
	{
		if (aClimateAlgo)
		{
			if (aClimateAlgo->type().present())
			{
				if (!std::strcmp(aClimateAlgo->type().c_str(), "FullyImplicit"))
				{
					return new FullyImplicitClimateAlgorithm(aClimateAlgo); // , aGlacier);
				}
			}
			else // no ClimateAlgo type provided => default algo
			{
				std::cerr << "Climate algorithm type not provided." << std::endl;
				return new DumbAlgorithm(/*aGlacier*/);
			}
		}
		else // ClimateAlgo component not provided => default algo
		{
			std::cerr << "Climate algorithm not provided." << std::endl;
			return new DumbAlgorithm(/*aGlacier*/);
		}
	}

}