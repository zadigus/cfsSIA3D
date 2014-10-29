#include "GlacierComponent.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

// TODO: write the debug output in a FILE

namespace N_Glacier {

	GlacierComponent::GlacierComponent(N_Configuration::Component* aComponent) 
		: ModelComponent(aComponent)
	{ // TODO: create class for logging purposes
		//std::cout << "Component " << _name; // TODO: write in log file
		//if (!_type.empty())
		//	std::cout << " of type " << _type;
		//std::cout << std::endl;

/*		if (aComponent)
		{
			N_Configuration::Component::SubComponent_sequence subComponents(aComponent->SubComponent());
			for (N_Configuration::Component::SubComponent_const_iterator it(subComponents.begin()); it != subComponents.end(); ++it)
			{
				if (!strcmp(it->name()->c_str(), "General"))
				{
					N_Configuration::SubComponent::Parameter_sequence  params(it->Parameter());
					for (N_Configuration::SubComponent::Parameter_const_iterator it(params.begin()); it != params.end(); ++it)
					{
						//std::cout << it->name() << ", " << (*it) << std::endl; // TODO: write in log file
						m_parameters.emplace(it->name(), (*it));
					}
				}
			}
		}*/
	}

	GlacierComponent::~GlacierComponent()
	{
		//m_parameters.clear();
	}

}