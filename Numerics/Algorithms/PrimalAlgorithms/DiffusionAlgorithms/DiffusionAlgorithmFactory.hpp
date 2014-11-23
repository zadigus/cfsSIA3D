#ifndef DIFFUSIONALGORITHMFACTORY_HPP_
#define DIFFUSIONALGORITHMFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	struct NumericsCoreParams;

	/*
	 *  The diffusion algorithms solve the discretized version of dH/dt = grad(D*grad(s))
	 */

	class DiffusionAlgorithmFactory
	{
	public:
		static PrimalAlgorithm* make(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo = nullptr); // TODO: make aDiffusionAlgo const
	};

}

#endif