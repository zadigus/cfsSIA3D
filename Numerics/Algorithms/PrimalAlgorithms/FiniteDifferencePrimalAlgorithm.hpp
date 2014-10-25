#ifndef FINITEDIFFERENCEPRIMALALGORITHM_HPP_
#define FINITEDIFFERENCEPRIMALALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	//class NumericsCoreParams;

	class FiniteDifferencePrimalAlgorithm : public PrimalAlgorithm
	{
		public:
			FiniteDifferencePrimalAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams,*/ N_Configuration::Component* aFiniteDifferenceAlgo);
			virtual ~FiniteDifferencePrimalAlgorithm();

			virtual void Run() = 0;

		protected:
			// Access the geometry in a "natural" way
			double& H(unsigned int i, unsigned int j);
			double& b(unsigned int i, unsigned int j);

		protected:
			// Ice thickness
			std::shared_ptr<Grid> _H;

			// Numerics parameters
			int _Nx;
			int _Ny;
			double _Dx;

		private:
			// Bedrock topography
			std::shared_ptr<Grid> _b;
	};

}

#endif