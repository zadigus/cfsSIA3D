#include "Primal.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelConfiguration.hpp"

#include "PrimalAlgorithms/PrimalAlgorithm.hpp"

// Factories
#include "PrimalAlgorithms/ClimateAlgorithms/ClimateAlgorithmFactory.hpp"
#include "PrimalAlgorithms/DiffusionAlgorithms/DiffusionAlgorithmFactory.hpp"
#include "PrimalAlgorithms/ProjectionAlgorithms/ProjectionAlgorithmFactory.hpp"

#include "NumericsCoreParams.hpp"

#include <iostream>

namespace N_Mathematics {

	Primal& Primal::getInstance() 
	{
		static Primal instance;
		return instance;
	}

	Primal::Primal()
		: m_DiffusionAlgo(nullptr)
		, m_ClimateAlgo(nullptr)
		, m_ProjectionAlgo(nullptr)
		, m_dt(0)
	{
		
	}

	Primal::~Primal()
	{

	}

	void Primal::init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf, const std::unique_ptr<NumericsCoreParams>& aNumCoreParams)
	{
		m_dt = aNumCoreParams->dt();
		m_ti = aNumCoreParams->ti();
		m_tf = aNumCoreParams->tf();

		N_Configuration::ModelConfiguration::Component_sequence compSeq(aMathConf->Component());
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); ++it) // TODO: use a const_iterator
		{
			LOG_INF("Math::Component " << it->name());

			if (!std::strcmp(it->name()->c_str(), "Diffusion"))
			{
				m_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(aNumCoreParams, &(*it)));
			}
			else if (!std::strcmp(it->name()->c_str(), "Climate"))
			{
				m_ClimateAlgo.reset(ClimateAlgorithmFactory::make(aNumCoreParams, &(*it)));
			}
			else if (!std::strcmp(it->name()->c_str(), "Projection"))
			{
				m_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(aNumCoreParams, &(*it)));
			}
			else
			{
				LOG_ERR("Mathematics component " << it->name()->c_str() << " unknown.");
			}
		}

		// Check configuration
		if (!m_DiffusionAlgo)
		{
			m_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make());
		}
		if (!m_ClimateAlgo)
		{
			m_ClimateAlgo.reset(ClimateAlgorithmFactory::make());
		}
		if (!m_ProjectionAlgo)
		{
			m_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make());
		}
	}

	void Primal::Run()
	{
		double currentTime(m_ti);
		while (currentTime < m_tf)
		{
			Iterate();
			currentTime += m_dt;
		}
	}

	void Primal::Iterate() //int l) // TODO: argument l is probably not necessary; let's just store the data in a vector ...
	{
		Diffusion();
		Climate();
		Projection();
		// TODO: handle the "Store" feature
	}

	void Primal::Diffusion()
	{
		m_DiffusionAlgo->Run(); 
	}

	void Primal::Climate()
	{
		m_ClimateAlgo->Run();
	}

	void Primal::Projection()
	{
		m_ProjectionAlgo->Run();
	}

}