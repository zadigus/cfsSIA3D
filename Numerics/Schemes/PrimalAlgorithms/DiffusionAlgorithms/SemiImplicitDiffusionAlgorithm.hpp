#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class SemiImplicitDiffusionAlgorithm : public PrimalAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo, const std::shared_ptr<Grid>& H);
			virtual ~SemiImplicitDiffusionAlgorithm();

			virtual void Run();

	};

}

#endif