#ifndef FINITEDIFFERENCEDIFFUSIONALGORITHM_HPP_
#define FINITEDIFFERENCEDIFFUSIONALGORITHM_HPP_

#include "FiniteDifferencePrimalAlgorithm.hpp"

class Grid;

namespace N_Glacier {
	class Rheology;
	class SlidingLaw;
}

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	//class NumericsCoreParams;
	class LinSyst;

	class FiniteDifferenceDiffusionAlgorithm : public FiniteDifferencePrimalAlgorithm
	{
		public:
			FiniteDifferenceDiffusionAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, */N_Configuration::Component* aDiffusionAlgo);
			virtual ~FiniteDifferenceDiffusionAlgorithm();

			virtual void Run() = 0;

		protected:
			// Compute the diffusivity D
			virtual void Diffusivity() = 0;
			// Compute the matrix elements
			virtual void ComputeElements() = 0;
			// compute norm of gradient of grid in the staggered grid; corresponds to alpha in the papers, which is |grad s|
			double StaggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H);
			// Access to _D in a more "natural" way
			double& D(unsigned int i, unsigned int j);
			double  Sl(unsigned int i, unsigned int j);

			// Getters
			double Gamma();
			double rhogn();
			double n();

		protected:
			// Physics models
			std::shared_ptr<N_Glacier::Rheology>   _Rh;
			std::shared_ptr<N_Glacier::SlidingLaw> _Sl;

			// Linear system
			std::unique_ptr<LinSyst> _LinSyst;

		private:
			// Diffusivity
			std::shared_ptr<Grid> _D;
	};
}

#endif