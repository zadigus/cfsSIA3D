#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

namespace N_Mathematics {

	class SemiImplicitDiffusionAlgorithm : public PrimalAlgorithm
	{
	public:
		SemiImplicitDiffusionAlgorithm(const std::shared_ptr<Grid>& H);
		virtual ~SemiImplicitDiffusionAlgorithm();

		virtual void Run() = 0;

	};

}

#endif