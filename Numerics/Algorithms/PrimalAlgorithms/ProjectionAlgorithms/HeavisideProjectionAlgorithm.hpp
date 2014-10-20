#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class HeavisideProjectionAlgorithm : public PrimalAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo);
			virtual ~HeavisideProjectionAlgorithm();

			virtual void Run();

		private:
			std::shared_ptr<Grid> _H;
	};

}

#endif