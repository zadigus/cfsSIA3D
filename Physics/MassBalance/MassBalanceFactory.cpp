#include "MassBalanceFactory.hpp"

#include "AcAmELA.hpp"
#include "GradELA.hpp"
#include "ZeroMB.hpp"

#include "PhysicsConfiguration.hpp"

MassBalance* MassBalanceFactory::make(Component* aMassBalance)
{ // TODO: print a notification about the chosen massbalance type
	if (aMassBalance->type().present())
	{
		if (aMassBalance->type()->c_str() == "AcAmELA")
			return new AcAmELA(aMassBalance);
		else if (aMassBalance->type() == "GradELA")
			return new GradELA(aMassBalance);
		else
			return new ZeroMB(aMassBalance); // if unknown, then set B = 0
	} 
	else
	{
		return new ZeroMB(aMassBalance); // if type not set, then set B = 0
	}
}