#include "FiniteDifferenceProjectionAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceProjectionAlgorithm::FiniteDifferenceProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo) 
		: FiniteDifferencePrimalAlgorithm(aProjectionAlgo)
	{
		
	}

	FiniteDifferenceProjectionAlgorithm::~FiniteDifferenceProjectionAlgorithm()
	{

	}

}