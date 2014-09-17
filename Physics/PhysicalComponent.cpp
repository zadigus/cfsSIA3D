#include "PhysicalComponent.hpp"

#include "PhysicsConfiguration.hpp"
#include <iostream>

PhysicalComponent::PhysicalComponent(Component* aComponent/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N*/)
//PhysicalComponent::PhysicalComponent(PhysicsConfiguration::Component_const_iterator& aComponent/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N*/)
//: _x(N)
: _name(aComponent->name()->c_str())
, _type(aComponent->type().present() ? aComponent->type()->c_str() : "") // TODO: handle the cases where there is no type (i.e. not specified)
{
	std::cout << "Component " << _name << " of type " << _type << std::endl;
	Component::Parameter_sequence  params(aComponent->Parameter());
	for (Component::Parameter_const_iterator it = params.begin(); it != params.end(); it++)
	{
		std::cout << it->name() << ", " << (*it) << std::endl;
		_parameters.emplace(it->name(), (*it));
	}
}

PhysicalComponent::~PhysicalComponent()
{
	_parameters.clear();
}