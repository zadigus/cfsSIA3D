#include "PrimalAlgorithm.hpp"

//#include "Numerics/Mesh/Grid.hpp"
//#include "Glacier/Glacier.hpp"
#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(N_Configuration::Component* aComponent/*, std::shared_ptr<N_Glacier::Glacier>& aGlacier*/) 
		// TODO: H is not sufficient; we need the whole glacier; 
		// is that a case where a callback would be necessary? (I need a glacier but I don't want PrimalAlgorithm to depend on a glacier)
		: _Glacier(nullptr)
	{ 
		if (aComponent)
		{

		}
	}

}