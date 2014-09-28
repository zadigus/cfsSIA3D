#include "PhysicsComponent.hpp"

#include "PhysicsCoreConfiguration.hpp"
#include "PhysicsConfiguration.hpp"
#include <iostream>

// TODO: write the debug output in a FILE

namespace N_Physics {

	PhysicsComponent::PhysicsComponent(Component* aComponent) // , std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N*/)
		//PhysicsComponent::PhysicsComponent(PhysicsConfiguration::Component_const_iterator& aComponent/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N*/)
		//: _x(N)
		: _name(aComponent->name()->c_str())
		, _type(aComponent->type().present() ? aComponent->type()->c_str() : "") // TODO: handle the cases where there is no type (i.e. not specified)
	{
		std::cout << "Component " << _name;
		if (!_type.empty())
			std::cout << " of type " << _type;
		std::cout << std::endl;

		Component::Parameter_sequence  params(aComponent->Parameter());
		for (Component::Parameter_const_iterator it = params.begin(); it != params.end(); it++)
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