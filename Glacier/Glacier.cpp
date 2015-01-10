#include "Glacier.hpp"

#include <algorithm>
#include <functional>

#include "PhysicsCoreParams.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"
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

using namespace std::placeholders;

namespace N_Glacier {

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

	void Glacier::setComponent(N_Configuration::Component aComp, PhysicsCoreParams aCore)
	{
		if (!aComp.name()->compare("MassBalance"))
		{ // doesn't work with ==
			m_MassBalance.reset(MassBalanceFactory::make(aCore, aComp));
		}
		else if (!aComp.name()->compare("Rheology"))
		{
			m_Rheology.reset(RheologyFactory::make(aCore, aComp));
		}
		else if (!aComp.name()->compare("SlidingLaw"))
		{
			m_SlidingLaw.reset(SlidingLawFactory::make(aComp));
		}
		else if (!aComp.name()->compare("Geometry"))
		{
			m_Geometry.reset(GeometryFactory::make(aComp));
		}
		else
		{
			LOG_ERR("Unknown component " << aComp.name()->c_str());
		}
	}

	void Glacier::init(const std::unique_ptr<N_Configuration::ModelConfiguration>& aPhysConf, const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysCoreConf)
	{
		if (!aPhysConf)
		{
			LOG_ERR("Glacier configuration not specified.");
			exit(EXIT_FAILURE);
		}

		PhysicsCoreParams physCore(aPhysCoreConf);

		// Read configuration
		N_Configuration::ModelConfiguration::Component_sequence compSeq = aPhysConf->Component();
		std::for_each(compSeq.begin(), compSeq.end(), std::bind(&Glacier::setComponent, this, _1, physCore));

		// Check configuration
		if (!m_MassBalance)
		{
			m_MassBalance.reset(MassBalanceFactory::make(physCore));
		}
		if (!m_SlidingLaw)
		{
			m_SlidingLaw.reset(SlidingLawFactory::make());
		}
		if (!m_Rheology)
		{ // nothing can happen without a rheology
			LOG_ERR("Missing compulsory rheology component.");
			exit(EXIT_FAILURE);
		}
		if (!m_Geometry)
		{
			LOG_ERR("Missing compulsory geometry component.");
			exit(EXIT_FAILURE);
		}

		// Resolve the sliding law dependence on the geometry and the rheology
		m_SlidingLaw->Generate(*b(), m_Rheology->n());
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