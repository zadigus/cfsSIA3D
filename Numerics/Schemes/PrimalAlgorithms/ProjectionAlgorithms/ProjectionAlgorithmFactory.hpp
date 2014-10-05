#ifndef PROJECTIONALGORITHMFACTORY_HPP_
#define PROJECTIONALGORITHMFACTORY_HPP_

#include <memory>

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;

	class ProjectionAlgorithmFactory
	{
	public:
		static PrimalAlgorithm* make(const std::shared_ptr<Grid>& H, N_Configuration::Component* aProjectionAlgo = nullptr);
	};

}

#endif