#ifndef FINITEDIFFERENCEPROJECTIONALGORITHM_HPP_
#define FINITEDIFFERENCEPROJECTIONALGORITHM_HPP_

#include "FiniteDifferencePrimalAlgorithm.hpp"

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	//class NumericsCoreParams;

	class FiniteDifferenceProjectionAlgorithm : public FiniteDifferencePrimalAlgorithm
	{
		public:
			FiniteDifferenceProjectionAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams,*/ N_Configuration::Component* aProjectionAlgo);
			virtual ~FiniteDifferenceProjectionAlgorithm();

			virtual void Run() = 0;
	};
}

#endif