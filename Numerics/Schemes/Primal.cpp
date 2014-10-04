#include "Primal.hpp"

#include "Configuration/ModelConfiguration.hpp"

//#include "PrimalAlgorithms/DiffusionAlgorithms/DiffusionAlgorithm.hpp"
//#include "PrimalAlgorithms/ClimateAlgorithms/ClimateAlgorithm.hpp"
//#include "PrimalAlgorithms/ProjectionAlgorithms/ProjectionAlgorithm.hpp"

#include "PrimalAlgorithms/PrimalAlgorithm.hpp"

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
		for (N_Configuration::ModelConfiguration::Component_const_iterator it = compSeq.begin(); it != compSeq.end(); ++it)
		{
			std::cout << "Math::Component " << it->name() << std::endl;
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