#ifndef FULLYIMPLICITCLIMATEALGORITHM_HPP_
#define FULLYIMPLICITCLIMATEALGORITHM_HPP_

#include "FiniteDifferenceClimateAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class NumericsCoreParams;

	/*
	 *  This class solves H^{l+1} - H^{l} = Dt * B(H^{l+1}) for H^{l+1} with a Newton method
	 */

	class FullyImplicitClimateAlgorithm : public FiniteDifferenceClimateAlgorithm
	{
		public:
			FullyImplicitClimateAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo);
			virtual ~FullyImplicitClimateAlgorithm();

			virtual void Run();

		protected:
			double& Hn(unsigned int i, unsigned int j);

		private:
			// Newton iterate
			std::unique_ptr<Grid> m_Hn;

			// Newton parameters
			double m_err;
			double m_tol;
			double m_updt; // opposite of Newton iteration update = -(x^{k+1}-x^{k}) = F / Fp
			double m_F; // value of the function of which we seek the zero
			double m_Fp; // value of the derivative of F

			// Numerics parameters
			double m_dt;
	};
}

#endif