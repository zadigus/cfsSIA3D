#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	class Glacier;
}

namespace N_Mathematics {

	class HeavisideProjectionAlgorithm : public PrimalAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo, std::shared_ptr<N_Glacier::Glacier>& aGlacier);
			virtual ~HeavisideProjectionAlgorithm();

			virtual void Run();
	};

}

#endif