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
		//GlacierComponent();
		virtual ~GlacierComponent();

		// Setter // Getter
		//virtual void Set(unsigned int i, double val) { _x[i] = val; }
		//double x(unsigned int i) const { return _x[i]; }
		//unsigned int N() const { return _x.size(); }

	protected:
		//std::vector<double> _x;  // physical parameters
		std::string _name; // component's name
		std::string _type; // component's type
		std::map<std::string, std::string> _parameters;


	};

}

#endif /* GLACIERCOMPONENT_H_ */
