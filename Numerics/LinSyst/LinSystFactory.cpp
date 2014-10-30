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

	LinSyst* LinSystFactory::make(N_Configuration::SubComponent* aLinSyst)
	{
		if (aLinSyst)
		{
			if (aLinSyst->name().present())
			{

#ifdef USE_PETSC
				if (!std::strcmp(aLinSyst->name()->c_str(), "PETSc"))
				{

					return new PETScLinSyst(aLinSyst); 
				}
#endif

#ifdef USE_TRILINOS
				if (!std::strcmp(aLinSyst->name()->c_str(), "Belos"))
				{
					return new BelosLinSyst(aLinSyst); 
				}
#endif

				std::cerr << "Unknow linear system with name " << aLinSyst->name() << std::endl;
				exit(EXIT_FAILURE);
			}
			else // no LinSyst type provided => default LinSyst
			{
				std::cerr << "Linear system type not provided." << std::endl; // TODO: write that in a log file
				//return new BelosLinSyst(); // TODO: put the iml++/sp++ linsyst 
				return nullptr;
			}
		}
		else // LinSyst sub-component not provided => default LinSyst
		{
			std::cerr << "Linear system not provided." << std::endl;
			//return new BelosLinSyst(); // TODO: put the iml++/sp++ linsyst 
			return nullptr;
		}
	}

}