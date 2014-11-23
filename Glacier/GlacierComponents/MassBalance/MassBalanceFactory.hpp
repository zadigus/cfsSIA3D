#ifndef MASSBALANCEFACTORY_H_
#define MASSBALANCEFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	
	class MassBalance;
	struct PhysicsCoreParams;

	class MassBalanceFactory
	{
		public:
			// factory methods
			static MassBalance* make(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aMassBalance = nullptr);
		};

}

#endif