#ifndef CLIMATEALGORITHMFACTORY_HPP_
#define CLIMATEALGORITHMFACTORY_HPP_

#include <memory>

//class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	class NumericsCoreParams;

	/*
	 *  The ClimateAlgorithms solve the discretized version of dH/dt = B
	 */

	class ClimateAlgorithmFactory 
	{
		public:
			static PrimalAlgorithm* make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams = std::unique_ptr<NumericsCoreParams>(nullptr), N_Configuration::Component* aClimateAlgo = nullptr);
	};

}

#endif