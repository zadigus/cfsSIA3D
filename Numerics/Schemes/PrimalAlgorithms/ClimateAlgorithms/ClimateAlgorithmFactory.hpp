#ifndef CLIMATEALGORITHMFACTORY_HPP_
#define CLIMATEALGORITHMFACTORY_HPP_

#include <memory>

//class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	class Glacier;
}

namespace N_Mathematics {

	class PrimalAlgorithm;

	class ClimateAlgorithmFactory 
	{
		public:
			static PrimalAlgorithm* make(std::shared_ptr<N_Glacier::Glacier>& aGlacier, N_Configuration::Component* aClimateAlgo = nullptr);
	};

}

#endif