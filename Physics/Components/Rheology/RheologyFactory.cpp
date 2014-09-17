#include "RheologyFactory.hpp"

#include "Rheology.hpp"
#include "PhysicsConfiguration.hpp" 
#include "PhysicsCoreParams.hpp"

Rheology* RheologyFactory::make(Component* aRheology, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
{
	return new Rheology(aRheology, aPhysCoreParams);
}