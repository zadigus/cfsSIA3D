#ifndef DUMBALGORITHM_HPP_
#define DUMBALGORITHM_HPP_

#include <memory>
#include "PrimalAlgorithm.hpp"

//class Grid;

namespace N_Configuration {
	class Component;
}

//namespace N_Glacier {
	//class Glacier;
//}

namespace N_Mathematics {

	class DumbAlgorithm : public PrimalAlgorithm
	{
		public:
			DumbAlgorithm(/*std::shared_ptr<N_Glacier::Glacier>& aGlacier*/);
			virtual ~DumbAlgorithm();
			virtual void Run(); 
	};

}

#endif