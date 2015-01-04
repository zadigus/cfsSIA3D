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

	struct NumericsCoreParams;

	class SemiImplicitDiffusionAlgorithm : public FiniteDifferenceDiffusionAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo);
			virtual ~SemiImplicitDiffusionAlgorithm();

			void setCrs();

		private:
			// Compute the CSR values of the linear system
			void fillLinSyst();
			// Compute the diffusivity D
			void computeDiffusivity();
			// Solve the linear system
			//void solveLinSyst();
			// Update the ice thickness
			void updateThickness();

		private:
			double m_C1; // dt / (2 dx)
			double m_C2; // dt / (2 dx^2)
	};

}

#endif