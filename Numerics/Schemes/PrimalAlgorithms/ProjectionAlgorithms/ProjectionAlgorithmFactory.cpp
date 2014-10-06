#include "ProjectionAlgorithmFactory.hpp"

#include "HeavisideProjectionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

//#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/Glacier.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* ProjectionAlgorithmFactory::make(std::shared_ptr<N_Glacier::Glacier>& aGlacier, N_Configuration::Component* aProjectionAlgo)
	{
		if (aProjectionAlgo)
		{
			if (aProjectionAlgo->type().present())
			{
				if (!std::strcmp(aProjectionAlgo->type().c_str(), "Heaviside"))
				{
					return new HeavisideProjectionAlgorithm(aProjectionAlgo, aGlacier);
				}
			}
			else // no ProjctionAlgo type provided => default algo
			{
				std::cerr << "Projection algorithm type not provided." << std::endl;
				return new DumbAlgorithm(aGlacier);
			}
		}
		else // ProjectionAlgo component not provided => default algo
		{
			std::cerr << "Projection algorithm type not provided." << std::endl;
			return new DumbAlgorithm(aGlacier);
		}
	}

}