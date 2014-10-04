#ifndef PROJECTALGORITHM_HPP_
#define PROJECTALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Mathematics {

	class HeavisideProjectionAlgorithm : public PrimalAlgorithm
	{
		public:
			HeavisideProjectionAlgorithm(const std::shared_ptr<Grid>& H);
			virtual ~HeavisideProjectionAlgorithm();

			virtual void Run();
	};

}

#endif