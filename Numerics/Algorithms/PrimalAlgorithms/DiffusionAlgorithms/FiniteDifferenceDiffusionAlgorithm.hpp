#ifndef FINITEDIFFERENCEDIFFUSIONALGORITHM_HPP_
#define FINITEDIFFERENCEDIFFUSIONALGORITHM_HPP_

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
	class LinSyst;

	class FiniteDifferenceDiffusionAlgorithm : public PrimalAlgorithm
	{
		public:
			FiniteDifferenceDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo);
			virtual ~FiniteDifferenceDiffusionAlgorithm();

			virtual void Run() = 0;

		protected:
			// Compute the diffusivity D
			virtual void Diffusivity() = 0;
			// Compute the matrix elements
			virtual void ComputeElements() = 0;

			// Access the ice thickness
			double& H(unsigned int i, unsigned int j);
			// compute norm of gradient of grid in the staggered grid; corresponds to alpha in the papers, which is |grad s|
			double StaggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H);

		protected:
			// Geometry
			std::shared_ptr<Grid> _b;
			std::shared_ptr<Grid> _H;

			// Physics models
			std::shared_ptr<N_Glacier::Rheology>   _Rh;
			std::shared_ptr<N_Glacier::SlidingLaw> _Sl;

			// Numerics parameters
			int _Nx;
			int _Ny;
			double _Dx;

			// CSR data
			std::vector<int> _nnz, _cols;
			std::vector<double> _A_values;
			std::vector<double> _b_values;

			// Linear system
			std::unique_ptr<LinSyst> _LinSyst;
	};
	
	inline double& FiniteDifferenceDiffusionAlgorithm::H(unsigned int i, unsigned int j)
	{
		return _H(i, j);
	}

}

#endif