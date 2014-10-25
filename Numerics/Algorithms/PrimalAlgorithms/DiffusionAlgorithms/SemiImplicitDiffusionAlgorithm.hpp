#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "FiniteDifferenceDiffusionAlgorithm.hpp"

class Grid;

namespace N_Glacier {
	class Rheology;
	class SlidingLaw;
}

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class NumericsCoreParams;

	class SemiImplicitDiffusionAlgorithm : public FiniteDifferenceDiffusionAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo);
			virtual ~SemiImplicitDiffusionAlgorithm();

			virtual void Run();

		protected:
			virtual void ComputeElements();

		private:
			// Compute the diffusivity D
			void Diffusivity();
	};

}

#endif