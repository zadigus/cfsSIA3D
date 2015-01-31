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
    class SubComponent;
}

namespace N_Mathematics {

	class LinSyst;

	class FiniteDifferenceDiffusionAlgorithm : public FiniteDifferencePrimalAlgorithm
	{
		public:
			//FiniteDifferenceDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo);
			FiniteDifferenceDiffusionAlgorithm(const N_Configuration::Component& aDiffusionAlgo);
			virtual ~FiniteDifferenceDiffusionAlgorithm();

			virtual void run();
			
			/*
			* Linear system setup
			*/
			virtual void setCrs() = 0;

		protected:
			/*
			 * Linear system resolution
			 */ 
			virtual void computeDiffusivity() = 0;
			virtual void fillLinSyst() = 0;
			void solveLinSyst();
			void updateThickness();

			/*
			 * Utility methods
			 */
			// compute norm of gradient of grid in the staggered grid; corresponds to alpha in the papers, which is |grad s|
			double staggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H);
			double& D(unsigned int i, unsigned int j); // diffusivity
			double  Sl(unsigned int i, unsigned int j);// sliding
			double Gamma();
			double rhogn();
			double n();

        private:
            void setAlgorithmComponent(const N_Configuration::SubComponent& aSubComponent);

		protected:
			// Physics models
			std::shared_ptr<N_Glacier::Rheology>   m_Rh;
			std::shared_ptr<N_Glacier::SlidingLaw> m_Sl;

			// Linear system
			std::unique_ptr<LinSyst> m_LinSyst;

		private:
			// Diffusivity
			std::unique_ptr<Grid> m_D;
	};
}

#endif
