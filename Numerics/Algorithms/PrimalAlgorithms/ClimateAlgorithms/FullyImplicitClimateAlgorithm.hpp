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

	/*
	 *  This class solves H^{l+1} - H^{l} = Dt * B(H^{l+1}) for H^{l+1} with a Newton method
	 */

	class FullyImplicitClimateAlgorithm : public PrimalAlgorithm
	{
		public:
			FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo); 
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
			double _updt;
			double _F;
			double _Fp;
	};

}

#endif