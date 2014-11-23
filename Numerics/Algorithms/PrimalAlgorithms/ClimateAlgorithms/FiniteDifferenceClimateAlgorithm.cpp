#include "FiniteDifferenceClimateAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceClimateAlgorithm::FiniteDifferenceClimateAlgorithm(N_Configuration::Component* aClimateAlgo) 
		: FiniteDifferencePrimalAlgorithm(aClimateAlgo)
		, m_B(m_glacier.B())
	{
		
	}

	FiniteDifferenceClimateAlgorithm::~FiniteDifferenceClimateAlgorithm()
	{

	}

}