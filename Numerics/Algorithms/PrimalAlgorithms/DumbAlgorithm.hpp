#ifndef DUMBALGORITHM_HPP_
#define DUMBALGORITHM_HPP_

#include <memory>
#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class DumbAlgorithm : public PrimalAlgorithm
	{
		public:
			DumbAlgorithm(/*std::shared_ptr<N_Glacier::Glacier>& aGlacier*/);
			virtual ~DumbAlgorithm();
			virtual void run(); 
	};

}

#endif