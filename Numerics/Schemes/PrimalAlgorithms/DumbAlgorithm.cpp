#include "DumbAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"

namespace N_Mathematics {

	DumbAlgorithm::DumbAlgorithm(const std::shared_ptr<Grid>& H)
		: PrimalAlgorithm(nullptr, H)
	{
		
	}

	DumbAlgorithm::~DumbAlgorithm()
	{

	}

	void DumbAlgorithm::Run()
	{
		// Do nothing
	}

}