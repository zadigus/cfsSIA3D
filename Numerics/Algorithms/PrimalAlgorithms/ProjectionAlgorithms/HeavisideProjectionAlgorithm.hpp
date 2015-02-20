#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "FiniteDifferenceProjectionAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
  class Glacier;
}

namespace N_Mathematics {

	struct NumericsCoreParams;

  class HeavisideProjectionAlgorithm : public PrimalAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aProjectionAlgo);
			virtual ~HeavisideProjectionAlgorithm();

      virtual void transform(N_Glacier::Glacier& a_Glacier);
	};

}

#endif
