#ifndef MASSBALANCEFACTORY_H_
#define MASSBALANCEFACTORY_H_

#include <memory>

class MassBalance;
class Component;
struct PhysicsCoreParams;

class MassBalanceFactory
{
public:
	//MassBalanceFactory();
	//~MassBalanceFactory();

	// factory method
	static MassBalance* make(Component* aMassBalance, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);

//protected:
	//std::unique_ptr<PhysicsConfiguration> _PhysConf;
};

#endif