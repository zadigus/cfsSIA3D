#ifndef PHYSICALCOMPONENT_H_
#define PHYSICALCOMPONENT_H_

//#include <vector>
#include <memory>
#include <string>
#include <map>

class Component;
//class PhysicsCoreConfiguration;
//#include "PhysicsConfiguration.hpp"

// Interface class for a general physical component
class PhysicalComponent {
public:
	PhysicalComponent(Component* aComponent); // , std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf);
	//PhysicalComponent(PhysicsConfiguration::Component_const_iterator& aComponent/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N=0*/);
	virtual ~PhysicalComponent();

	// Setter // Getter
	//virtual void Set(unsigned int i, double val) { _x[i] = val; }
	//double x(unsigned int i) const { return _x[i]; }
	//unsigned int N() const { return _x.size(); }

protected:
	//std::vector<double> _x;  // physical parameters
	std::string _name; // component's name
	std::string _type; // component's type
	std::map<std::string, double> _parameters;


};

#endif /* PHYSICALCOMPONENT_H_ */
