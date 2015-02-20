#ifndef MODELCOMPONENT_HPP_
#define MODELCOMPONENT_HPP_

#include "Configuration/ModelConfiguration.hpp"

#include <string>
#include <map>
#include <functional>

// Interface class for a general model component
class ModelComponent 
{ 
	public:
		ModelComponent(const N_Configuration::Component& aComponent);
		ModelComponent();
		virtual ~ModelComponent();

	protected:
		void setParameter(const N_Configuration::Parameter& aParam);

	protected:
		std::string m_name; // component's name
		std::string m_type; // component's type
		std::map<std::string, std::string> m_Parameters;
};

#endif /* MODELCOMPONENT_HPP_ */
