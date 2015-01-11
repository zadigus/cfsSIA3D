#ifndef CLIMATEALGORITHMFACTORY_HPP_
#define CLIMATEALGORITHMFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	struct NumericsCoreParams;

	/*
	 *  The ClimateAlgorithms solve the discretized version of dH/dt = B
	 */

	class ClimateAlgorithmFactory 
	{
		public:
			//static PrimalAlgorithm* make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo = nullptr);
			static PrimalAlgorithm* make(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aClimateAlgo);
			//static PrimalAlgorithm* make(const NumericsCoreParams& aNumCoreParams);
	};

}

#endif