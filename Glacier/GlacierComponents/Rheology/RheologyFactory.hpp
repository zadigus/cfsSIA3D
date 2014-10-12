#ifndef RHEOLOGYFACTORY_H_
#define RHEOLOGYFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {

	class Rheology;
	struct PhysicsCoreParams;

	class RheologyFactory
	{
	public:
		// factory method
		static Rheology* make(std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams = std::unique_ptr<PhysicsCoreParams>(nullptr), N_Configuration::Component* aRheology = nullptr);
	};
}

#endif