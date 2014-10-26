#ifndef GLACIERCOMPONENT_H_
#define GLACIERCOMPONENT_H_

#include <memory>
#include <string>
#include <map>


namespace N_Configuration {
	class Component;
}

namespace N_Glacier {

	// Interface class for a general physical component
	class GlacierComponent {
	public:
		GlacierComponent(N_Configuration::Component* aComponent = nullptr);
		virtual ~GlacierComponent();

	protected:
		std::string m_name; // component's name
		std::string m_type; // component's type
		std::map<std::string, std::string> m_parameters;
	};
}

#endif /* GLACIERCOMPONENT_H_ */
