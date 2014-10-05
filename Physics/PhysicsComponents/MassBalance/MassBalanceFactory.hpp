#ifndef MASSBALANCEFACTORY_H_
#define MASSBALANCEFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Physics {
	
	class MassBalance;
	struct PhysicsCoreParams;

	class MassBalanceFactory
	{
		public:
			// factory methods
			static MassBalance* make(N_Configuration::Component* aMassBalance = nullptr, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams = std::unique_ptr<PhysicsCoreParams>(nullptr));
		};

}

#endif