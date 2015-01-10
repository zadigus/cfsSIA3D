#include "ModelComponent.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

//ModelComponent::ModelComponent(N_Configuration::Component* aComponent) 
ModelComponent::ModelComponent(const N_Configuration::Component& aComponent)
	//: m_name(aComponent != nullptr ? aComponent->name()->c_str() : "")
	//, m_type(aComponent != nullptr ? (aComponent->type().present() ? aComponent->type()->c_str() : "") : "")
	: m_name(aComponent.name()->c_str())
	, m_type(aComponent.type().present() ? aComponent.type()->c_str() : "")
{ 
	//if (aComponent)
	//{
		N_Configuration::Component::SubComponent_sequence subComponents(aComponent.SubComponent());
		for (N_Configuration::Component::SubComponent_const_iterator it(subComponents.begin()); it != subComponents.end(); ++it)
		{
			if (!strcmp(it->name()->c_str(), "General")) // TODO: write predicate and apply algorithm for_each
			{
				N_Configuration::SubComponent::Parameter_sequence  params(it->Parameter());
				for (N_Configuration::SubComponent::Parameter_const_iterator it(params.begin()); it != params.end(); ++it)
				{
					m_parameters.emplace(it->name(), (*it));
				}
			}
		}
	//}
}

ModelComponent::ModelComponent()
{
	
}

ModelComponent::~ModelComponent()
{

}