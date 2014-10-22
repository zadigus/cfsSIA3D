#ifndef SEMIIMPLICITDIFFUSIONALGORITHM_HPP_
#define SEMIIMPLICITDIFFUSIONALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

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

	class SemiImplicitDiffusionAlgorithm : public PrimalAlgorithm
	{
		public:
			SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo);
			virtual ~SemiImplicitDiffusionAlgorithm();

			virtual void Run();

		private:
			// Compute the diffusivity D
			void Diffusivity();

			// compute norm of gradient of grid in the staggered grid; corresponds to alpha in the papers, which is |grad s|
			double StaggeredGradSurfNorm(unsigned int i, unsigned int j);

		private:
			// Geometry
			std::shared_ptr<Grid> _b;
			std::shared_ptr<Grid> _H;

			// Physics models
			std::shared_ptr<N_Glacier::Rheology>   _Rh;
			std::shared_ptr<N_Glacier::SlidingLaw> _Sl;

			// Diffusivity
			std::shared_ptr<Grid> _D;

			// Numerics parameters
			int _Nx;
			int _Ny;
			double _Dx;
	};

}

#endif