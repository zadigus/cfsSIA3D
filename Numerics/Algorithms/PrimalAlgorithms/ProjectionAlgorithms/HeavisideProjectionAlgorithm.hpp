#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "FiniteDifferenceProjectionAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	struct NumericsCoreParams;

	class HeavisideProjectionAlgorithm : public FiniteDifferenceProjectionAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo);
			virtual ~HeavisideProjectionAlgorithm();

			virtual void run();
	};

}

#endif