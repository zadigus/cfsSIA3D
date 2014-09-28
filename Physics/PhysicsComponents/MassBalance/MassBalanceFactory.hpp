#ifndef MASSBALANCEFACTORY_H_
#define MASSBALANCEFACTORY_H_

#include <memory>

namespace N_Physics {
	
	class Component;
	class MassBalance;
	struct PhysicsCoreParams;

	class MassBalanceFactory
	{
	public:
		//MassBalanceFactory();
		//~MassBalanceFactory();

		// factory methods
		static MassBalance* make(Component* aMassBalance = nullptr, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams = std::unique_ptr<PhysicsCoreParams>(nullptr));

		//protected:
		//std::unique_ptr<PhysicsConfiguration> _PhysConf;
	};

}

#endif