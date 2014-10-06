#include "DiffusionAlgorithmFactory.hpp"

#include "SemiImplicitDiffusionAlgorithm.hpp"
#include "DumbAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"

//#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/Glacier.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm* DiffusionAlgorithmFactory::make(std::shared_ptr<N_Glacier::Glacier>& aGlacier, N_Configuration::Component* aDiffusionAlgo)
	{
		if (aDiffusionAlgo)
		{
			if (aDiffusionAlgo->type().present())
			{
				if (!std::strcmp(aDiffusionAlgo->type().c_str(), "SemiImplicit"))
				{
					return new SemiImplicitDiffusionAlgorithm(aDiffusionAlgo, H);
				}
			}
			else // no DiffusionAlgo type provided => default algo
			{
				std::cerr << "Diffusion algorithm type not provided." << std::endl;
				return new DumbAlgorithm(H);
			}
		}
		else // DiffusionAlgo component not provided => default algo
		{
			std::cerr << "Diffusion algorithm not provided." << std::endl;
			return new DumbAlgorithm(H);
		}
	}

}