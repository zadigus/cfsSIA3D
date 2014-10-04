#ifndef FULLYIMPLICITCLIMATEALGORITHM_HPP_
#define FULLYIMPLICITCLIMATEALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Mathematics {

	class FullyImplicitClimateAlgorithm : public PrimalAlgorithm
	{
	public:
		FullyImplicitClimateAlgorithm(const std::shared_ptr<Grid>& H);
		virtual ~FullyImplicitClimateAlgorithm();

		virtual void Run();

	};

}

#endif