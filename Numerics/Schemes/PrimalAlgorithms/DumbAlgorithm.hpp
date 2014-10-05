#ifndef DUMBALGORITHM_HPP_
#define DUMBALGORITHM_HPP_

#include <memory>
#include "PrimalAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class DumbAlgorithm : public PrimalAlgorithm
	{
		public:
			DumbAlgorithm(const std::shared_ptr<Grid>& H);
			virtual ~DumbAlgorithm();
			virtual void Run(); 
	};

}

#endif