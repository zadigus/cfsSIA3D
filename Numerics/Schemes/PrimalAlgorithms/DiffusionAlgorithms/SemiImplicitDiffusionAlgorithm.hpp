#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	class Glacier;
}

namespace N_Mathematics {

	class SemiImplicitDiffusionAlgorithm : public PrimalAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo, std::shared_ptr<N_Glacier::Glacier>& aGlacier);
			virtual ~SemiImplicitDiffusionAlgorithm();

			virtual void Run();

	};

}

#endif