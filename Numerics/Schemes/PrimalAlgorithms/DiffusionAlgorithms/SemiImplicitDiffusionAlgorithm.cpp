#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const std::shared_ptr<Grid>& H)
		: PrimalAlgorithm(H)
	{

	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
	
	}
}