#ifndef FULLYIMPLICITCLIMATEALGORITHM_HPP_
#define FULLYIMPLICITCLIMATEALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

class Grid;

namespace N_Glacier {
	class MassBalance;
}

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class NumericsCoreParams;

	/*
	 *  This class solves H^{l+1} - H^{l} = Dt * B(H^{l+1}) for H^{l+1} with a Newton method
	 */

	class FullyImplicitClimateAlgorithm : public PrimalAlgorithm
	{
		public:
			FullyImplicitClimateAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo);
			virtual ~FullyImplicitClimateAlgorithm();

			virtual void Run();

		private:
			// Newton iterates
			std::shared_ptr<Grid> _H;
			std::unique_ptr<Grid> _Hn;

			// Glacier geometry
			std::shared_ptr<Grid> _b;

			// Glacier mass-balance
			std::shared_ptr<N_Glacier::MassBalance> _B;

			// Newton parameters
			double _err;
			double _tol;
			double _updt; // opposite of Newton iteration update = -(x^{k+1}-x^{k}) = F / Fp
			double _F; // value of the function of which we seek the zero
			double _Fp; // value of the derivative of F

			// Numerics parameters
			double _dt;
	};

}

#endif