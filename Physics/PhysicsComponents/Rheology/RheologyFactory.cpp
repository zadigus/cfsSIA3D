#include "RheologyFactory.hpp"

#include "Rheology.hpp"
#include "PhysicsConfiguration.hpp" 
#include "PhysicsCoreParams.hpp"

namespace N_Physics {

	Rheology* RheologyFactory::make(Component* aRheology, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
	{
		return new Rheology(aRheology, aPhysCoreParams);
	}

}