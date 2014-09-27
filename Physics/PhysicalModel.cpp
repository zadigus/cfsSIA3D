#include "PhysicalModel.hpp"
#include "PhysicsCoreParams.hpp"

#include <iostream>
#include "Components/PhysicsCoreConfiguration.hpp"
#include "Components/PhysicsConfiguration.hpp"
#include "Components/PhysicsComponent.hpp"

// Factories
#include "Components/MassBalance/MassBalanceFactory.hpp"
#include "Components/Rheology/RheologyFactory.hpp"
#include "Components/SlidingLaw/SlidingLawFactory.hpp"

// Physical components
#include "Components/MassBalance/MassBalance.hpp"
#include "Components/Rheology/Rheology.hpp"
#include "Components/SlidingLaw/SlidingLaw.hpp"

PhysicalModel::PhysicalModel(std::unique_ptr<PhysicsConfiguration>& aPhysConf, std::unique_ptr<PhysicsCoreConfiguration>& aPhysCoreConf)
: _MassBalance(NULL)
, _Rheology(NULL)
, _SlidingLaw(NULL)
{

	std::unique_ptr<PhysicsCoreParams> physCore(new PhysicsCoreParams(aPhysCoreConf));

	PhysicsConfiguration::Component_sequence compSeq = aPhysConf->Component();
	for (PhysicsConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); it++)
	{
		if (!std::strcmp(it->name()->c_str(), "MassBalance")) // TODO: handle with the case where one of these components is not present in the config
		{ // doesn't work with ==
			_MassBalance.reset(MassBalanceFactory::make(&(*it), physCore));
		}
		else if (!std::strcmp(it->name()->c_str(), "Rheology"))
		{
			_Rheology.reset(RheologyFactory::make(&(*it), physCore));
		}
		else if (!std::strcmp(it->name()->c_str(), "SlidingLaw"))
		{
			_SlidingLaw.reset(SlidingLawFactory::make(&(*it)));
		}
		else 
		{
			std::cerr << "Unknown component " << it->name()->c_str() << "." << std::endl;
		}

	}
}

PhysicalModel::~PhysicalModel()
{

}