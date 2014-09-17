#ifndef RHEOLOGYFACTORY_H_
#define RHEOLOGYFACTORY_H_

#include <memory>

class Rheology;
class Component; 
struct PhysicsCoreParams;

class RheologyFactory
{
public:
	// factory method
	static Rheology* make(Component* aRheology, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
};

#endif