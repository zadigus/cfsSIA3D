#include "Primal.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include "PrimalAlgorithms/PrimalAlgorithm.hpp"

// Factories
#include "PrimalAlgorithms/ClimateAlgorithms/ClimateAlgorithmFactory.hpp"
#include "PrimalAlgorithms/DiffusionAlgorithms/DiffusionAlgorithmFactory.hpp"
#include "PrimalAlgorithms/ProjectionAlgorithms/ProjectionAlgorithmFactory.hpp"

#include <iostream>

namespace N_Mathematics {

	Primal& Primal::getInstance()
	{
		static Primal instance;
		return instance;
	}

	Primal::Primal()
		: _DiffusionAlgo(nullptr)
		, _ClimateAlgo(nullptr)
		, _ProjectionAlgo(nullptr)
	{
		
	}

	Primal::~Primal()
	{

	}

	void Primal::init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf)
	{
		// TODO: configure the Diffusion, Climate, and Projection algorithms with FACTORIES that read each component of aMathConf
		N_Configuration::ModelConfiguration::Component_sequence compSeq(aMathConf->Component());
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); ++it) // TODO: use a const_iterator
		{
			std::cout << "Math::Component " << it->name() << std::endl;
			if (!std::strcmp(it->name()->c_str(), "Diffusion"))
			{
				_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H(), &(*it))); // TODO: get _H from Glacier Singleton which should return a reference to the std::shared_ptr<Grid>
			}
			else if (!std::strcmp(it->name()->c_str(), "Climate"))
			{
				_ClimateAlgo.reset(ClimateAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H(), &(*it)));
			}
			else if (!std::strcmp(it->name()->c_str(), "Projection"))
			{
				_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H(), &(*it)));
			}
			else
			{
				std::cerr << "Mathematics component " << it->name()->c_str() << " unknown." << std::endl;
			}
		}

		// Check configuration
		if (!_DiffusionAlgo)
		{
			_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H()));
		}
		if (!_ClimateAlgo)
		{
			_ClimateAlgo.reset(ClimateAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H()));
		}
		if (!_ProjectionAlgo)
		{
			_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(N_Glacier::Glacier::getInstance().H()));
		}
	}

	void Primal::Diffusion()
	{
		_DiffusionAlgo->Run(); // TODO: that should update the ice thickness
	}

	void Primal::Climate()
	{
		_ClimateAlgo->Run();
	}

	void Primal::Projection()
	{
		_ProjectionAlgo->Run();
	}

}