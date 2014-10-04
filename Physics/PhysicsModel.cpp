#include "PhysicsModel.hpp"
#include "PhysicsCoreParams.hpp"

#include <iostream>
#include "Configuration/PhysicsCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsComponents/PhysicsComponent.hpp"

// Factories
#include "PhysicsComponents/MassBalance/MassBalanceFactory.hpp"
#include "PhysicsComponents/Rheology/RheologyFactory.hpp"
#include "PhysicsComponents/SlidingLaw/SlidingLawFactory.hpp"

// Physical components
#include "PhysicsComponents/MassBalance/MassBalance.hpp"
#include "PhysicsComponents/Rheology/Rheology.hpp"
#include "PhysicsComponents/SlidingLaw/SlidingLaw.hpp"

namespace N_Physics {

	PhysicsModel& PhysicsModel::getInstance()
	{
		static PhysicsModel instance;
		return instance;
	}

	PhysicsModel::PhysicsModel()
		: _MassBalance(NULL)
		, _Rheology(NULL)
		, _SlidingLaw(NULL)
	{

	}

	PhysicsModel::~PhysicsModel()
	{

	}

	void PhysicsModel::init(std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, std::unique_ptr<N_Configuration::PhysicsCoreConfiguration>& aPhysCoreConf)
	{
		std::unique_ptr<PhysicsCoreParams> physCore(new PhysicsCoreParams(aPhysCoreConf));

		// Read configuration
		N_Configuration::ModelConfiguration::Component_sequence compSeq = aPhysConf->Component();
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); it++)
		{
			if (!it->name()->compare("MassBalance"))
			{ // doesn't work with ==
				_MassBalance.reset(MassBalanceFactory::make(&(*it), physCore));
			}
			else if (!it->name()->compare("Rheology"))
			{
				_Rheology.reset(RheologyFactory::make(&(*it), physCore));
			}
			else if (!it->name()->compare("SlidingLaw"))
			{
				_SlidingLaw.reset(SlidingLawFactory::make(&(*it)));
			}
			else
			{
				std::cerr << "Unknown component " << it->name()->c_str() << "." << std::endl;
			}
		}

		// Check configuration
		if (!_MassBalance)
		{
			//std::cout << "Setting MassBalance to zero." << std::endl;
			//_MassBalance.reset(new ZeroMB);
			_MassBalance.reset(MassBalanceFactory::make());
		}
		if (!_SlidingLaw)
		{
			//std::cout << "Setting SlidingLaw to zero." << std::endl;
			_SlidingLaw.reset(SlidingLawFactory::make());
		}
		if (!_Rheology)
		{ // nothing can happen without a rheology
			std::cerr << "Missing compulsory rheology component." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

}