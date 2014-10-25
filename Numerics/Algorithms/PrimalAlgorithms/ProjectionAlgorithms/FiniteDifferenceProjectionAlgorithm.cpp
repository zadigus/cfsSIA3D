#include "FiniteDifferenceProjectionAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceProjectionAlgorithm::FiniteDifferenceProjectionAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams,*/ N_Configuration::Component* aProjectionAlgo) 
		: FiniteDifferencePrimalAlgorithm(aProjectionAlgo)
	{
		
	}

	FiniteDifferenceProjectionAlgorithm::~FiniteDifferenceProjectionAlgorithm()
	{

	}

}