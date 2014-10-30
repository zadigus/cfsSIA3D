#ifndef LINSYSTFACTORY_HPP_
#define LINSYSTFACTORY_HPP_

#include <memory>

namespace N_Configuration {
	class SubComponent; 
}

namespace N_Mathematics {

	class LinSyst;

	/*
	 *  The LinSysts solve A*x = b
	 */

	class LinSystFactory 
	{
		public:
			static LinSyst* make(N_Configuration::SubComponent* aLinSyst);
	};

}

#endif