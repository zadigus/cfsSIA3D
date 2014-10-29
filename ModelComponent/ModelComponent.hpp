#ifndef MODELCOMPONENT_HPP_
#define MODELCOMPONENT_HPP_

#include <memory>
#include <string>
#include <map>

namespace N_Configuration {
	class Component;
}

// Interface class for a general model component
class ModelComponent 
{ 
	public:
		ModelComponent(N_Configuration::Component* aComponent = nullptr);
		virtual ~ModelComponent();

	protected:
		std::string m_name; // component's name
		std::string m_type; // component's type
		std::map<std::string, std::string> m_parameters;
};

#endif /* MODELCOMPONENT_HPP_ */