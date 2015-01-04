#include "LinSystFactory.hpp"
#include "LinSystConfig.hpp"
#include "Utility/Logger/Logger.hpp"

#ifdef USE_PETSC
#include "PETScLinSyst.hpp"
#endif

#ifdef USE_TRILINOS
#include "BelosLinSyst.hpp"
#endif

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	LinSyst* LinSystFactory::make(N_Configuration::SubComponent* aLinSyst)
	{
		if (aLinSyst)
		{
			/*N_Configuration::SubComponent::Parameter_sequence params(aLinSyst->Parameter());
			for (N_Configuration::SubComponent::Parameter_iterator it(params.begin()); it != params.end(); ++it)
			{

			}*/

			if (aLinSyst->type().present())
			{

#ifdef USE_PETSC
				if (!std::strcmp(aLinSyst->type()->c_str(), "PETSc"))
				{
					LOG_INF("Creating PETSc linear system.");
					return new PETScLinSyst(aLinSyst); 
				}
#endif

#ifdef USE_TRILINOS
				if (!std::strcmp(aLinSyst->type()->c_str(), "Belos"))
				{
					LOG_INF("Creating Belos linear system.");
					return new BelosLinSyst(aLinSyst); 
				}
#endif

				LOG_ERR("Unknown linear system of type " << aLinSyst->type());
				exit(EXIT_FAILURE);
			}
			else // no LinSyst type provided => default LinSyst
			{
				LOG_WRN("Linear system type not provided.");
				//return new BelosLinSyst(); // TODO: put the iml++/sp++ linsyst 
				return nullptr;
			}
		}
		else // LinSyst sub-component not provided => default LinSyst
		{
			LOG_WRN("Linear system not provided.");
			//return new BelosLinSyst(); // TODO: put the iml++/sp++ linsyst 
			return nullptr;
		}
	}

}