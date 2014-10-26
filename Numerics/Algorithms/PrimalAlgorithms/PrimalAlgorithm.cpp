#include "PrimalAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	PrimalAlgorithm::PrimalAlgorithm(N_Configuration::Component* aComponent)
		: m_glacier(N_Glacier::Glacier::getInstance())
	{ 
		if (aComponent)
		{
			N_Configuration::Component::Parameter_sequence  params(aComponent->Parameter());
			for (N_Configuration::Component::Parameter_const_iterator it = params.begin(); it != params.end(); ++it)
			{
				//std::cout << it->name() << ", " << (*it) << std::endl; // TODO: write in a log file
				m_parameters.emplace(it->name(), (*it));
			}
		}
	}

}