#include "SlidingLawFactory.hpp"

//#include "SlidingLaw.hpp"
#include "AltitudeSL.hpp"
#include "ConstantSL.hpp"
#include "PhysicsConfiguration/PhysicsConfiguration.hpp" // TODO: define!

SlidingLawFactory::SlidingLawFactory(PhysicsConfiguration* aPhysConf)
: _PhysConf(aPhysConf)
{

}

SlidingLawFactory::~SlidingLawFactory()
{

}

SlidingLaw* SlidingLawFactory::make()
{
	// TODO: based on _PhysConf, decide what subclass to build
}