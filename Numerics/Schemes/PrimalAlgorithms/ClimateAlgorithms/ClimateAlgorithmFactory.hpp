#ifndef CLIMATEALGORITHMFACTORY_HPP_
#define CLIMATEALGORITHMFACTORY_HPP_

#include <memory>

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;

	class ClimateAlgorithmFactory 
	{
		public:
			static PrimalAlgorithm* make(const std::shared_ptr<Grid>& H, N_Configuration::Component* aClimateAlgo = nullptr);
	};

}

#endif