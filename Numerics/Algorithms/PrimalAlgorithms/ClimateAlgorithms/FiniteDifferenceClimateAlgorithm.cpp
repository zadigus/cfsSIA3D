#include "FiniteDifferenceClimateAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceClimateAlgorithm::FiniteDifferenceClimateAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, */N_Configuration::Component* aClimateAlgo) 
		: FiniteDifferencePrimalAlgorithm(aClimateAlgo)
		, _B(_glacier->B())
	{
		
	}

	FiniteDifferenceClimateAlgorithm::~FiniteDifferenceClimateAlgorithm()
	{

	}

}