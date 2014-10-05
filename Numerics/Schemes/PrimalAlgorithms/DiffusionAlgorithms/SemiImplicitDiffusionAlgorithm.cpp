#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo, const std::shared_ptr<Grid>& H)
		: PrimalAlgorithm(aDiffusionAlgo, H)
	{

	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
	
	}
}