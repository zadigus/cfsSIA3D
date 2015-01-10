#include "FiniteDifferenceProjectionAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	//FiniteDifferenceProjectionAlgorithm::FiniteDifferenceProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo) 
	FiniteDifferenceProjectionAlgorithm::FiniteDifferenceProjectionAlgorithm(const N_Configuration::Component& aProjectionAlgo)
		: FiniteDifferencePrimalAlgorithm(aProjectionAlgo)
	{
		
	}

	FiniteDifferenceProjectionAlgorithm::~FiniteDifferenceProjectionAlgorithm()
	{

	}

}