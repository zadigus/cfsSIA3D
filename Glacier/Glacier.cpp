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
		: m_MassBalance(nullptr)
		, m_Rheology(nullptr)
		, m_SlidingLaw(nullptr)
		, m_Geometry(nullptr)
	{

	}

	Glacier::~Glacier()
	{

	}

	void Glacier::setComponent(const N_Configuration::Component& a_Comp, const PhysicsCoreParams& a_Core)
	{
		if (!a_Comp.name()->compare("MassBalance"))
		{ // doesn't work with ==
			m_MassBalance.reset(MassBalanceFactory::make(a_Core, a_Comp));
		}
		else if (!a_Comp.name()->compare("Rheology"))
		{
			m_Rheology.reset(RheologyFactory::make(a_Core, a_Comp));
		}
		else if (!a_Comp.name()->compare("SlidingLaw"))
		{
			m_SlidingLaw.reset(SlidingLawFactory::make(a_Comp));
		}
		else if (!a_Comp.name()->compare("Geometry"))
		{
			m_Geometry.reset(GeometryFactory::make(a_Comp));
		}
		else
		{
			LOG_ERR("Unknown component " << a_Comp.name()->c_str());
		}
	}

  void Glacier::init(std::unique_ptr<N_Configuration::ModelConfiguration> a_PhysConf, std::unique_ptr<N_Configuration::ModelCoreConfiguration> a_PhysCoreConf)
	{
		if (!a_PhysConf)
		{
			LOG_ERR("Glacier configuration not specified.");
			exit(EXIT_FAILURE);
		}

		PhysicsCoreParams physCore(a_PhysCoreConf);

		// Read configuration
		N_Configuration::ModelConfiguration::Component_sequence compSeq = a_PhysConf->Component();
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
		m_SlidingLaw->Generate(m_Geometry, m_Rheology->n());
	}

}
