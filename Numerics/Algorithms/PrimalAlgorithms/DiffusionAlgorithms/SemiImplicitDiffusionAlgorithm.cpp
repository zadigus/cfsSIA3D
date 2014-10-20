#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo) 
		: PrimalAlgorithm(aDiffusionAlgo)
	{

	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
	
	}
}