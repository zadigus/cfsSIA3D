#include "FullyImplicitClimateAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(const std::shared_ptr<Grid>& H)
		: PrimalAlgorithm(H)
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