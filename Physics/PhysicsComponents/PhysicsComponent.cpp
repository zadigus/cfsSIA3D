#include "PhysicsComponent.hpp"

#include "Configuration/PhysicsCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include <iostream>

// TODO: write the debug output in a FILE

namespace N_Physics {

	PhysicsComponent::PhysicsComponent(N_Configuration::Component* aComponent) 
		: _name(aComponent->name()->c_str())
		, _type(aComponent->type().present() ? aComponent->type()->c_str() : "") // TODO: handle the cases where there is no type (i.e. not specified)
	{
		std::cout << "Component " << _name;
		if (!_type.empty())
			std::cout << " of type " << _type;
		std::cout << std::endl;

		N_Configuration::Component::Parameter_sequence  params(aComponent->Parameter());
		for (N_Configuration::Component::Parameter_const_iterator it = params.begin(); it != params.end(); it++)
		{
			std::cout << it->name() << ", " << (*it) << std::endl;
			_parameters.emplace(it->name(), (*it));
		}
	}

	PhysicsComponent::PhysicsComponent()
	{

	}

	PhysicsComponent::~PhysicsComponent()
	{
		_parameters.clear();
	}

}