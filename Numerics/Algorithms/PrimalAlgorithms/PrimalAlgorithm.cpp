#include "PrimalAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(const N_Configuration::Component& aComponent)
		: ModelComponent(aComponent)
		, m_glacier(N_Glacier::Glacier::getInstance()) 
	{ 

	}

	PrimalAlgorithm::PrimalAlgorithm()
		: ModelComponent()
		, m_glacier(N_Glacier::Glacier::getInstance())
	{

	}

	PrimalAlgorithm::~PrimalAlgorithm()
	{

	}

}