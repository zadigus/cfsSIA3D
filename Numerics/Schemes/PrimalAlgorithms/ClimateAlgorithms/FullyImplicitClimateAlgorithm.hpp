#ifndef FULLYIMPLICITCLIMATEALGORITHM_HPP_
#define FULLYIMPLICITCLIMATEALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

//namespace N_Glacier {
	//class Glacier;
//}

namespace N_Mathematics {

	class FullyImplicitClimateAlgorithm : public PrimalAlgorithm
	{
	public:
		FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo); // , std::shared_ptr<N_Glacier::Glacier>& aGlacier);
		virtual ~FullyImplicitClimateAlgorithm();

		virtual void Run();

	};

}

#endif