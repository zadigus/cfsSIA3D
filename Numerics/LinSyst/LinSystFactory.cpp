#include "LinSystFactory.hpp"
#include "LinSystConfig.hpp"

#ifdef USE_PETSC
#include "PETScLinSyst.hpp"
#endif

#ifdef USE_TRILINOS
#include "BelosLinSyst.hpp"
#endif

#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	LinSyst* LinSystFactory::make(unsigned int MS, N_Configuration::Component* aLinSyst) // TODO: make use of SubComponents
	{
		if (aLinSyst)
		{
			if (aLinSyst->type().present())
			{

#ifdef USE_PETSC
				if (!std::strcmp(aLinSyst->type()->c_str(), "PETSc"))
				{

					return new PETScLinSyst(MS, aLinSyst); 
				}
#endif

#ifdef USE_TRILINOS
				if (!std::strcmp(aLinSyst->type()->c_str(), "Belos"))
				{
					return new BelosLinSyst(MS, aLinSyst); 
				}
#endif

				std::cerr << "Unknow linear system of type " << aLinSyst->type() << std::endl;
				exit(EXIT_FAILURE);
			}
			else // no LinSyst type provided => default LinSyst
			{
				std::cerr << "Linear system type not provided." << std::endl; // TODO: write that in a log file
				return new BelosLinSyst(MS); // TODO: put the iml++/sp++ linsyst 
			}
		}
		else // LinSyst sub-component not provided => default LinSyst
		{
			std::cerr << "Linear system not provided." << std::endl;
			return new BelosLinSyst(MS); // TODO: put the iml++/sp++ linsyst 
		}
	}

}