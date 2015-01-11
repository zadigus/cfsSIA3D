#ifndef PROJECTIONALGORITHMFACTORY_HPP_
#define PROJECTIONALGORITHMFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class Component;
}


namespace N_Mathematics {

	class PrimalAlgorithm;
	struct NumericsCoreParams;

	/*
	 *  The projection algorithms ensure the positivity of the ice thickness
	 */

	class ProjectionAlgorithmFactory
	{
	public:
		//static PrimalAlgorithm* make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo = nullptr);
		static PrimalAlgorithm* make(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aProjectionAlgo);
		//static PrimalAlgorithm* make(const NumericsCoreParams& aNumCoreParams);
	};

}

#endif