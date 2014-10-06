#include "FullyImplicitClimateAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
//#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/Glacier.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo, std::shared_ptr<N_Glacier::Glacier>& aGlacier)
		: PrimalAlgorithm(aClimateAlgo, aGlacier)
	{

	}

	FullyImplicitClimateAlgorithm::~FullyImplicitClimateAlgorithm()
	{

	}

	void FullyImplicitClimateAlgorithm::Run()
	{
		//Grid H(*(_H.get()));
	}

}