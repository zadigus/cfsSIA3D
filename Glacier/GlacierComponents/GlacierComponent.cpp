#include "GlacierComponent.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

// TODO: write the debug output in a FILE

namespace N_Glacier {

	GlacierComponent::GlacierComponent(N_Configuration::Component* aComponent) 
		: m_name(aComponent != nullptr ? aComponent->name()->c_str() : "")
		, m_type(aComponent != nullptr ? (aComponent->type().present() ? aComponent->type()->c_str() : "") : "")
	{
		//std::cout << "Component " << _name; // TODO: write in log file
		//if (!_type.empty())
		//	std::cout << " of type " << _type;
		//std::cout << std::endl;

		if (aComponent)
		{
			N_Configuration::Component::Parameter_sequence  params(aComponent->Parameter());
			for (N_Configuration::Component::Parameter_const_iterator it = params.begin(); it != params.end(); ++it)
			{
				//std::cout << it->name() << ", " << (*it) << std::endl; // TODO: write in log file
				m_parameters.emplace(it->name(), (*it));
			}
		}
	}

	GlacierComponent::~GlacierComponent()
	{
		m_parameters.clear();
	}

}