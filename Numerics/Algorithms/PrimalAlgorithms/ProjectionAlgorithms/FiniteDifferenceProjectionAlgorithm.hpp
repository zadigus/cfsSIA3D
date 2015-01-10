#ifndef FINITEDIFFERENCEPROJECTIONALGORITHM_HPP_
#define FINITEDIFFERENCEPROJECTIONALGORITHM_HPP_

#include "FiniteDifferencePrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class FiniteDifferenceProjectionAlgorithm : public FiniteDifferencePrimalAlgorithm
	{
		public:
			//FiniteDifferenceProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo);
			FiniteDifferenceProjectionAlgorithm(const N_Configuration::Component& aProjectionAlgo);
			virtual ~FiniteDifferenceProjectionAlgorithm();

			virtual void run() = 0;
	};
}

#endif