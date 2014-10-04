#ifndef RHEOLOGYFACTORY_H_
#define RHEOLOGYFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Physics {

	class Rheology;
	struct PhysicsCoreParams;

	class RheologyFactory
	{
	public:
		// factory method
		static Rheology* make(N_Configuration::Component* aRheology, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
	};
}

#endif