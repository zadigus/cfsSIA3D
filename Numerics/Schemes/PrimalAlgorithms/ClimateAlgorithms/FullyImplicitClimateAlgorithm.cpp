#include "FullyImplicitClimateAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo, const std::shared_ptr<Grid>& H)
		: PrimalAlgorithm(aClimateAlgo, H)
	{

	}

	FullyImplicitClimateAlgorithm::~FullyImplicitClimateAlgorithm()
	{

	}

	void FullyImplicitClimateAlgorithm::Run()
	{
		Grid H(*(_H.get()));
	}

}