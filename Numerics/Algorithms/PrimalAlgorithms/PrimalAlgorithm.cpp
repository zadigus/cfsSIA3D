#include "PrimalAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(N_Configuration::Component* aComponent)
		: ModelComponent(aComponent)
		, m_glacier(N_Glacier::Glacier::getInstance()) // TODO: is that really the right thing to do? 
		// this has the advantage that the glacier mustn't be passed as an argument to a whole bunch of class ctors
		//, m_glacier(aGlacier)
	{ 

	}

}