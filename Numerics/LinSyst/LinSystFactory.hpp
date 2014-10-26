#ifndef LINSYSTFACTORY_HPP_
#define LINSYSTFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class Component; // TODO: use SubComponents here
}

namespace N_Mathematics {

	class LinSyst;

	/*
	 *  The LinSysts solve A*x = b
	 */

	class LinSystFactory 
	{
		public:
			static LinSyst* make(unsigned int MS, N_Configuration::Component* aLinSyst);
	};

}

#endif