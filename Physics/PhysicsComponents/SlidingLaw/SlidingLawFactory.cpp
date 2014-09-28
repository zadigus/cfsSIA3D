#include "SlidingLawFactory.hpp"

//#include "SlidingLaw.hpp"
#include "AltitudeSL.hpp"
#include "ConstantSL.hpp"
#include "ZeroSL.hpp"
#include "PhysicsConfiguration.hpp" 

#include <iostream>

namespace N_Physics {

	SlidingLaw* SlidingLawFactory::make(Component* aSlidingLaw)
	{
		if (aSlidingLaw)
		{
			if (aSlidingLaw->type().present())
			{
				if (aSlidingLaw->type()->compare("Altitude"))
					return new AltitudeSL(aSlidingLaw);
				else if (aSlidingLaw->type()->compare("Constant"))
					return new ConstantSL(aSlidingLaw);
				else
				{
					std::cout << "Unknown type " << aSlidingLaw->type() << ". Setting SlidingLaw to zero." << std::endl;
					return new ZeroSL(/*aSlidingLaw*/); // if unknown, then set B = 0
				}
			}
			else
			{
				std::cout << "Type not specified. Setting SlidingLaw to zero." << std::endl;
				return new ZeroSL(/*aSlidingLaw*/); // if type not set, then set B = 0
			}
		}
		else
		{
			std::cout << "No configuration provided. Setting SlidingLaw to zero." << std::endl;
			return new ZeroSL();
		}
	}

}