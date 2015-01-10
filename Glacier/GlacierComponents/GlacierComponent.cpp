#include "GlacierComponent.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

namespace N_Glacier {

	//GlacierComponent::GlacierComponent(N_Configuration::Component* aComponent) 
	GlacierComponent::GlacierComponent(const N_Configuration::Component& aComponent)
		: ModelComponent(aComponent)
	{ 

	}

	GlacierComponent::GlacierComponent()
		: ModelComponent()
	{

	}

	GlacierComponent::~GlacierComponent()
	{

	}

}