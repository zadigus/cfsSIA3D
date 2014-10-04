#include "SlidingLawFactory.hpp"

//#include "SlidingLaw.hpp"
#include "AltitudeSL.hpp"
#include "ConstantSL.hpp"
#include "ZeroSL.hpp"
#include "Configuration/ModelConfiguration.hpp" 

#include <iostream>

namespace N_Physics {

	SlidingLaw* SlidingLawFactory::make(N_Configuration::Component* aSlidingLaw)
	{
		if (aSlidingLaw)
		{
			if (aSlidingLaw->type().present())
			{
				//if (aSlidingLaw->type()->compare("Altitude"))
				if (!std::strcmp(aSlidingLaw->type()->c_str(), "Altitude"))
					return new AltitudeSL(aSlidingLaw);
				//else if (aSlidingLaw->type()->compare("Constant"))
				else if (!std::strcmp(aSlidingLaw->type()->c_str(), "Constant"))
					return new ConstantSL(aSlidingLaw);
				else
				{
					std::cout << "Unknown type " << aSlidingLaw->type() << ". Setting SlidingLaw to zero." << std::endl;
					return new ZeroSL(); // if unknown, then set B = 0
				}
			}
			else
			{
				std::cout << "Type not specified. Setting SlidingLaw to zero." << std::endl;
				return new ZeroSL(); // if type not set, then set B = 0
			}
		}
		else
		{
			std::cout << "No configuration provided. Setting SlidingLaw to zero." << std::endl;
			return new ZeroSL();
		}
	}

}