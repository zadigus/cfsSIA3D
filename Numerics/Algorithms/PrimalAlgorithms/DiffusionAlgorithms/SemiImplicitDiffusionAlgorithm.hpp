#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class NumericsCoreParams;

	class SemiImplicitDiffusionAlgorithm : public PrimalAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo);
			virtual ~SemiImplicitDiffusionAlgorithm();

			virtual void Run();

	};

}

#endif