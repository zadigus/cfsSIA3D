#ifndef FINITEDIFFERENCECLIMATEALGORITHM_HPP_
#define FINITEDIFFERENCECLIMATEALGORITHM_HPP_

#include "FiniteDifferencePrimalAlgorithm.hpp"

namespace N_Glacier {
	class MassBalance;
}

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class FiniteDifferenceClimateAlgorithm : public FiniteDifferencePrimalAlgorithm
	{
		public:
			//FiniteDifferenceClimateAlgorithm(N_Configuration::Component* aClimateAlgo);
			FiniteDifferenceClimateAlgorithm(const N_Configuration::Component& aClimateAlgo);
			virtual ~FiniteDifferenceClimateAlgorithm();

			virtual void run() = 0;

		protected:
			// Glacier mass-balance
			std::shared_ptr<N_Glacier::MassBalance> m_B;
	};
}

#endif