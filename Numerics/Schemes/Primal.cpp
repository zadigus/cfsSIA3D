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

	//Primal* Primal::_instance = nullptr;

	Primal& Primal::getInstance() 
	{
		static Primal instance;
		//_instance = &instance;
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

	/*Primal::Primal(const Primal& rhs)
	{
		_instance = rhs._instance;
	}

	Primal& Primal::operator= (const Primal& rhs)
	{
		if (this != &rhs)
		{
			_instance = rhs._instance;
		}
		return *this;
	}*/

	void Primal::init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf, std::shared_ptr<N_Glacier::Glacier>& aGlacier)
	{
		N_Configuration::ModelConfiguration::Component_sequence compSeq(aMathConf->Component());
		for (N_Configuration::ModelConfiguration::Component_iterator it = compSeq.begin(); it != compSeq.end(); ++it) // TODO: use a const_iterator
		{
			std::cout << "Math::Component " << it->name() << std::endl;
			if (!std::strcmp(it->name()->c_str(), "Diffusion"))
			{
				_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(/*aGlacier, */&(*it))); 
			}
			else if (!std::strcmp(it->name()->c_str(), "Climate"))
			{
				_ClimateAlgo.reset(ClimateAlgorithmFactory::make(/*aGlacier, */&(*it)));
			}
			else if (!std::strcmp(it->name()->c_str(), "Projection"))
			{
				_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(/*aGlacier, */&(*it)));
			}
			else
			{
				std::cerr << "Mathematics component " << it->name()->c_str() << " unknown." << std::endl;
			}
		}

		// Check configuration
		if (!_DiffusionAlgo)
		{
			_DiffusionAlgo.reset(DiffusionAlgorithmFactory::make(/*aGlacier*/));
		}
		if (!_ClimateAlgo)
		{
			_ClimateAlgo.reset(ClimateAlgorithmFactory::make(/*aGlacier*/));
		}
		if (!_ProjectionAlgo)
		{
			_ProjectionAlgo.reset(ProjectionAlgorithmFactory::make(/*aGlacier*/));
		}

		// Add glacier reference
		_DiffusionAlgo->setGlacierRef(aGlacier);
		_ClimateAlgo->setGlacierRef(aGlacier);
		_ProjectionAlgo->setGlacierRef(aGlacier);
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