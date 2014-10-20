#ifndef PROJECTIONALGORITHMFACTORY_HPP_
#define PROJECTIONALGORITHMFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class Component;
}


namespace N_Mathematics {

	class PrimalAlgorithm;
	class NumericsCoreParams;

	/*
	 *  The projection algorithms ensure the positivity of the ice thickness
	 */

	class ProjectionAlgorithmFactory
	{
	public:
		static PrimalAlgorithm* make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams = std::unique_ptr<NumericsCoreParams>(nullptr), N_Configuration::Component* aProjectionAlgo = nullptr);
	};

}

#endif