#include "RheologyFactory.hpp"

#include "Rheology.hpp"
#include "Configuration/ModelConfiguration.hpp" 
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	Rheology* RheologyFactory::make(std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aRheology)
	{
		return new Rheology(aPhysCoreParams, aRheology);
	}

}