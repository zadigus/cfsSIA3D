#include "Glacier.hpp"
#include "PhysicsCoreParams.hpp"

#include <iostream>
#include "Configuration/ModelCoreConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

// Factories
#include "GlacierComponents/MassBalance/MassBalanceFactory.hpp"
#include "GlacierComponents/Rheology/RheologyFactory.hpp"
#include "GlacierComponents/SlidingLaw/SlidingLawFactory.hpp"
#include "GlacierComponents/Geometry/GeometryFactory.hpp"

// Physical components
//#include "GlacierComponents/GlacierComponent.hpp"
#include "GlacierComponents/MassBalance/MassBalance.hpp"
#include "GlacierComponents/Rheology/Rheology.hpp"
#include "GlacierComponents/SlidingLaw/SlidingLaw.hpp"
#include "GlacierComponents/Geometry/Geometry.hpp"

namespace N_Glacier {

	/*Glacier& Glacier::getInstance() 
	{
		static Glacier instance;
		return instance;
	}*/

	std::shared_ptr<Glacier>& Glacier::getInstance()
	{
		static std::shared_ptr<Glacier> instance = nullptr;
		if (!instance)
		{
			instance.reset(new Glacier);
		}
		return instance;
	}

	Glacier::Glacier()
		: _MassBalance(NULL)
		, _Rheology(NULL)
		, _SlidingLaw(NULL)
		, _Geometry(NULL)
	{

	}

	Glacier::~Glacier()
	{

	}

	void Glacier::init(const std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysCoreConf)
	{
		std::unique_ptr<PhysicsCoreParams> physCore(new PhysicsCoreParams(aPhysCoreConf));

		// Read configuration
		N_Configuration::ModelConfiguration::Component_sequence compSeq = aPhysConf->Component();
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); it++)
		{
			if (!it->name()->compare("MassBalance"))
			{ // doesn't work with ==
				_MassBalance.reset(MassBalanceFactory::make(physCore, &(*it)));
			}
			else if (!it->name()->compare("Rheology"))
			{
				_Rheology.reset(RheologyFactory::make(physCore, &(*it)));
			}
			else if (!it->name()->compare("SlidingLaw"))
			{
				_SlidingLaw.reset(SlidingLawFactory::make(&(*it)));
			}
			else if (!it->name()->compare("Geometry"))
			{
				_Geometry.reset(GeometryFactory::make(&(*it)));
			}
			else
			{
				std::cerr << "Unknown component " << it->name()->c_str() << "." << std::endl;
			}
		}

		// Check configuration
		if (!_MassBalance)
		{
			_MassBalance.reset(MassBalanceFactory::make());
		}
		if (!_SlidingLaw)
		{
			_SlidingLaw.reset(SlidingLawFactory::make());
		}
		if (!_Rheology)
		{ // nothing can happen without a rheology
			std::cerr << "Missing compulsory rheology component." << std::endl;
			exit(EXIT_FAILURE);
		}
		if (!_Geometry)
		{
			std::cerr << "Missing compulsory geometry component." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	std::shared_ptr<Grid> Glacier::b()
	{
		return _Geometry->b();
	}

	std::shared_ptr<Grid> Glacier::H()
	{
		return _Geometry->H();
	}

}

/*Glacier::Glacier(const Glacier& rhs)
{
_instance = rhs._instance;
}

Glacier& Glacier::operator= (const Glacier& rhs)
{
if (this != &rhs)
{
_instance = rhs._instance;
}
return *this;
}*/