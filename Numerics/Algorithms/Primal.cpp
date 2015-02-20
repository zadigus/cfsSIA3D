#include "Primal.hpp"

#include <algorithm>
#include <functional>

#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"
#include "PrimalAlgorithms/PrimalAlgorithm.hpp"
#include "PrimalAlgorithms/DumbAlgorithm.hpp"

// Factories
#include "PrimalAlgorithms/ClimateAlgorithms/ClimateAlgorithmFactory.hpp"
#include "PrimalAlgorithms/DiffusionAlgorithms/DiffusionAlgorithmFactory.hpp"
#include "PrimalAlgorithms/ProjectionAlgorithms/ProjectionAlgorithmFactory.hpp"

#include "NumericsCoreParams.hpp"

using namespace std::placeholders;

namespace N_Mathematics {

	Primal::Primal()
		: m_DiffusionAlgo(nullptr)
		, m_ClimateAlgo(nullptr)
		, m_ProjectionAlgo(nullptr)
		, m_dt(0)
    , m_ti(0)
    , m_tf(0)
	{
	
	}

	Primal::~Primal()
	{

	}

	void Primal::setComponent(const N_Configuration::Component& aComp, const NumericsCoreParams& aCore)
	{
		if (!std::strcmp(aComp.name()->c_str(), "Diffusion"))
		{
			m_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(aCore, aComp));
		}
		else if (!std::strcmp(aComp.name()->c_str(), "Climate"))
		{
			m_ClimateAlgo.reset(ClimateAlgorithmFactory::make(aCore, aComp));
		}
		else if (!std::strcmp(aComp.name()->c_str(), "Projection"))
		{
			m_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(aCore, aComp));
		}
		else
		{
			LOG_ERR("Mathematics component " << aComp.name()->c_str() << " unknown.");
		}
	}

  void Primal::init(std::unique_ptr<N_Configuration::ModelConfiguration> aMathConf, std::unique_ptr<N_Configuration::ModelCoreConfiguration> aNumCoreConf)
	{
		if (!aMathConf)
		{
			LOG_ERR("Numerics model configuration not specified.");
			exit(EXIT_FAILURE);
		}

		NumericsCoreParams numCore(aNumCoreConf);

		m_dt = numCore.dt();
		m_ti = numCore.ti();
		m_tf = numCore.tf();

		N_Configuration::ModelConfiguration::Component_sequence compSeq(aMathConf->Component());
		std::for_each(compSeq.begin(), compSeq.end(), std::bind(&Primal::setComponent, this, _1, numCore));

		// Check configuration
		if (!m_DiffusionAlgo)
		{
			LOG_WRN("Diffusion algorithm not provided. Setting algorithm that does not nothing.");
			m_DiffusionAlgo.reset(new DumbAlgorithm());
		}
		if (!m_ClimateAlgo)
		{
			LOG_WRN("Climate algorithm not provided. Setting algorithm that does not nothing.");
			m_ClimateAlgo.reset(new DumbAlgorithm());
		}
		if (!m_ProjectionAlgo)
		{
			LOG_WRN("Projection algorithm not provided. Setting algorithm that does not nothing.");
			m_ProjectionAlgo.reset(new DumbAlgorithm());
		}
	}

	void Primal::run()
	{
		double currentTime(m_ti);
		while (currentTime < m_tf)
		{
			LOG_INF("Current time : " << currentTime);
      iterate();
			currentTime += m_dt;
		}
	}

  void Primal::iterate()
	{
    doDiffusion();
    doClimate();
    doProjection();
		// TODO: handle the "Store" feature
	}

  void Primal::doDiffusion()
	{
    m_DiffusionAlgo->transform(m_Glacier);
	}

  void Primal::doClimate()
	{
    m_ClimateAlgo->transform(m_Glacier);
	}

  void Primal::doProjection()
	{
    m_ProjectionAlgo->transform(m_Glacier);
	}

}
