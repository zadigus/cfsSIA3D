#include "Primal.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include "PrimalAlgorithms/PrimalAlgorithm.hpp"

// Factories
#include "PrimalAlgorithms/ClimateAlgorithms/ClimateAlgorithmFactory.hpp"
#include "PrimalAlgorithms/DiffusionAlgorithms/DiffusionAlgorithmFactory.hpp"
#include "PrimalAlgorithms/ProjectionAlgorithms/ProjectionAlgorithmFactory.hpp"

// Glacier
#include "Glacier/Glacier.hpp"

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
	{
		
	}

	Primal::~Primal()
	{

	}

	void Primal::init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf, std::shared_ptr<N_Glacier::Glacier>& aGlacier)
	{
		N_Configuration::ModelConfiguration::Component_sequence compSeq(aMathConf->Component());
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); ++it) // TODO: use a const_iterator
		{
			std::cout << "Math::Component " << it->name() << std::endl;
			if (!std::strcmp(it->name()->c_str(), "Diffusion"))
			{
				m_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(&(*it))); 
			}
			else if (!std::strcmp(it->name()->c_str(), "Climate"))
			{
				m_ClimateAlgo.reset(ClimateAlgorithmFactory::make(&(*it)));
			}
			else if (!std::strcmp(it->name()->c_str(), "Projection"))
			{
				m_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(&(*it)));
			}
			else
			{
				std::cerr << "Mathematics component " << it->name()->c_str() << " unknown." << std::endl;
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

		// Add glacier reference
		m_DiffusionAlgo->setGlacierRef(aGlacier);
		m_ClimateAlgo->setGlacierRef(aGlacier);
		m_ProjectionAlgo->setGlacierRef(aGlacier);
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