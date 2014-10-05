#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class HeavisideProjectionAlgorithm : public PrimalAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo, const std::shared_ptr<Grid>& H);
			virtual ~HeavisideProjectionAlgorithm();

			virtual void Run();
	};

}

#endif