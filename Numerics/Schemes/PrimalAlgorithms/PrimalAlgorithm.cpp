#include "PrimalAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(N_Configuration::Component* aComponent, const std::shared_ptr<Grid>& H)
		: _H(H)
	{
		if (aComponent)
		{

		}
	}

}