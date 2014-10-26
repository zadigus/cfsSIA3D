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
#include "GlacierComponents/MassBalance/MassBalance.hpp"
#include "GlacierComponents/Rheology/Rheology.hpp"
#include "GlacierComponents/SlidingLaw/SlidingLaw.hpp"
#include "GlacierComponents/Geometry/Geometry.hpp"

namespace N_Glacier {

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
		: m_MassBalance(NULL)
		, m_Rheology(NULL)
		, m_SlidingLaw(NULL)
		, m_Geometry(NULL)
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
				m_MassBalance.reset(MassBalanceFactory::make(physCore, &(*it)));
			}
			else if (!it->name()->compare("Rheology"))
			{
				m_Rheology.reset(RheologyFactory::make(physCore, &(*it)));
			}
			else if (!it->name()->compare("SlidingLaw"))
			{
				m_SlidingLaw.reset(SlidingLawFactory::make(&(*it)));
			}
			else if (!it->name()->compare("Geometry"))
			{
				m_Geometry.reset(GeometryFactory::make(&(*it)));
			}
			else
			{
				std::cerr << "Unknown component " << it->name()->c_str() << "." << std::endl;
			}
		}

		// Check configuration
		if (!m_MassBalance)
		{
			m_MassBalance.reset(MassBalanceFactory::make());
		}
		if (!m_SlidingLaw)
		{
			m_SlidingLaw.reset(SlidingLawFactory::make());
		}
		if (!m_Rheology)
		{ // nothing can happen without a rheology
			std::cerr << "Missing compulsory rheology component." << std::endl;
			exit(EXIT_FAILURE);
		}
		if (!m_Geometry)
		{
			std::cerr << "Missing compulsory geometry component." << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	std::shared_ptr<Grid> Glacier::b()
	{
		return m_Geometry->b();
	}

	std::shared_ptr<Grid> Glacier::H()
	{
		return m_Geometry->H();
	}

	std::shared_ptr<Grid> Glacier::gradbx()
	{
		return m_Geometry->gradbx();
	}

	std::shared_ptr<Grid> Glacier::gradby()
	{
		return m_Geometry->gradby();
	}

}