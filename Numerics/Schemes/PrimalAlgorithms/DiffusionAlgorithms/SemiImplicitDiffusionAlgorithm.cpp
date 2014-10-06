#include "SemiImplicitDiffusionAlgorithm.hpp"

//#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/Glacier.hpp"

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo, std::shared_ptr<N_Glacier::Glacier>& aGlacier)
		: PrimalAlgorithm(aDiffusionAlgo, aGlacier)
	{

	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
	
	}
}