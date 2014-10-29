#include "ModelComponent.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

// TODO: write the debug output in a FILE

ModelComponent::ModelComponent(N_Configuration::Component* aComponent) 
	: m_name(aComponent != nullptr ? aComponent->name()->c_str() : "")
	, m_type(aComponent != nullptr ? (aComponent->type().present() ? aComponent->type()->c_str() : "") : "")
{ // TODO: create class for logging purposes
	//std::cout << "Component " << _name; // TODO: write in log file
	//if (!_type.empty())
	//	std::cout << " of type " << _type;
	//std::cout << std::endl;

	if (aComponent)
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
	}
}

ModelComponent::~ModelComponent()
{
	//m_parameters.clear();
}