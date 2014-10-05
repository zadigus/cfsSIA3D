#ifndef FULLYIMPLICITCLIMATEALGORITHM_HPP_
#define FULLYIMPLICITCLIMATEALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class FullyImplicitClimateAlgorithm : public PrimalAlgorithm
	{
	public:
		FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo, const std::shared_ptr<Grid>& H);
		virtual ~FullyImplicitClimateAlgorithm();

		virtual void Run();

	};

}

#endif