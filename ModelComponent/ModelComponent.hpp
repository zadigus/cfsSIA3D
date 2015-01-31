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

//class IsSubComponent : public std::unary_function<N_Configuration::SubComponent, bool>
//{
//	public:
//		IsSubComponent(const std::string& aSubComponentName) : m_SubComponentName(aSubComponentName) { }

//		bool operator() (const N_Configuration::SubComponent& aSubComponent) const
//		{
//			return !aSubComponent.name()->compare(m_SubComponentName);
//		}

//	private:
//		std::string m_SubComponentName;
//};

#endif /* MODELCOMPONENT_HPP_ */
