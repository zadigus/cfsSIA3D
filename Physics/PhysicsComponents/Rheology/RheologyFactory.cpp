#include "RheologyFactory.hpp"

#include "Rheology.hpp"
#include "Configuration/ModelConfiguration.hpp" 
#include "PhysicsCoreParams.hpp"

namespace N_Physics {

	Rheology* RheologyFactory::make(N_Configuration::Component* aRheology, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
	{
		return new Rheology(aRheology, aPhysCoreParams);
	}

}