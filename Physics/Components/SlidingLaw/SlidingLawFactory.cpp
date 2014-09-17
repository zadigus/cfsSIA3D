#include "SlidingLawFactory.hpp"

//#include "SlidingLaw.hpp"
#include "AltitudeSL.hpp"
#include "ConstantSL.hpp"
#include "ZeroSL.hpp"
#include "PhysicsConfiguration.hpp" 

SlidingLaw* SlidingLawFactory::make(Component* aSlidingLaw)
{
	if (aSlidingLaw->type().present())
	{
		if (aSlidingLaw->type()->c_str() == "Altitude")
			return new AltitudeSL(aSlidingLaw);
		else if (aSlidingLaw->type()->c_str() == "Constant")
			return new ConstantSL(aSlidingLaw);
		else
			return new ZeroSL(aSlidingLaw); // if unknown, then set B = 0
	}
	else
	{
		return new ZeroSL(aSlidingLaw); // if type not set, then set B = 0
	}

}