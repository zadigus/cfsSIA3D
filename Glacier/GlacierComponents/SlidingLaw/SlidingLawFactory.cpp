#include "SlidingLawFactory.hpp"
#include "Utility/Logger/Logger.hpp"

#include "AltitudeSL.hpp"
#include "ConstantSL.hpp"
#include "ZeroSL.hpp"
#include "Configuration/ModelConfiguration.hpp" 

namespace N_Glacier {

	SlidingLaw* SlidingLawFactory::make(N_Configuration::Component* aSlidingLaw)
	{
		if (aSlidingLaw)
		{
			if (aSlidingLaw->type().present())
			{
				if (!std::strcmp(aSlidingLaw->type()->c_str(), "Altitude"))
				{
					LOG_INF("Setting SlidingLaw Altitude.");
					return new AltitudeSL(aSlidingLaw);
				}
				else if (!std::strcmp(aSlidingLaw->type()->c_str(), "Constant"))
				{
					LOG_INF("Setting SlidingLaw Constant.");
					return new ConstantSL(aSlidingLaw);
				}
				else
				{
					LOG_WRN("Unknown type " << aSlidingLaw->type() << ". Setting SlidingLaw to zero.");
					return new ZeroSL(); // if unknown, then set B = 0
				}
			}
			else
			{
				LOG_WRN("Type not specified. Setting SlidingLaw to zero.");
				return new ZeroSL(); // if type not set, then set B = 0
			}
		}
		else
		{
			LOG_WRN("No configuration provided. Setting SlidingLaw to zero."); 
			return new ZeroSL();
		}
	}

}