#ifndef PHYSICSCOMPONENT_H_
#define PHYSICSCOMPONENT_H_

//#include <vector>
#include <memory>
#include <string>
#include <map>

class Component;
//class PhysicsCoreConfiguration;
//#include "PhysicsConfiguration.hpp"

// Interface class for a general physical component
class PhysicsComponent {
public:
	PhysicsComponent(Component* aComponent); // , std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf);
	//PhysicsComponent(PhysicsConfiguration::Component_const_iterator& aComponent/*std::shared_ptr<PhysicsConfiguration>& physConf, std::string compName*/ /*unsigned int N=0*/);
	virtual ~PhysicsComponent();

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

#endif /* PHYSICSCOMPONENT_H_ */
