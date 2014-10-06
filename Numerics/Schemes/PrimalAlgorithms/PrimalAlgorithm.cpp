#include "PrimalAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(N_Configuration::Component* aComponent, const std::shared_ptr<Grid>& H) // TODO: H is not sufficient; we need the whole glacier; is that a case where a callback would be necessary? (I need a glacier but I don't want PrimalAlgorithm to depend on a glacier)
		: _H(H)
	{ // TODO: GEt the thickness here from Glacier instance
		if (aComponent)
		{

		}
	}

}