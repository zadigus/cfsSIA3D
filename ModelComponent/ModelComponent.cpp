#include "ModelComponent.hpp"

#include <algorithm>

#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

#include <iostream>

using namespace std::placeholders;

ModelComponent::ModelComponent(const N_Configuration::Component& aComponent)
	: m_name(aComponent.name()->c_str())
	, m_type(aComponent.type().present() ? aComponent.type()->c_str() : "")
{ 

	N_Configuration::Component::SubComponent_sequence subComponents(aComponent.SubComponent());
	N_Configuration::Component::SubComponent_iterator it(std::find_if(subComponents.begin(), subComponents.end(), IsSubComponent("General")));
	if (it != subComponents.end())
	{
		N_Configuration::SubComponent::Parameter_sequence  params(it->Parameter());
		std::for_each(params.begin(), params.end(), std::bind(&ModelComponent::setParameter, this, _1));
	}
}

ModelComponent::ModelComponent()
{
	
}

ModelComponent::~ModelComponent()
{

}

void ModelComponent::setParameter(const N_Configuration::Parameter& aParam)
{
	m_Parameters.emplace(aParam.name(), aParam.data());
}