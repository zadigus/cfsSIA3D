#ifndef SLIDINGLAWFACTORY_H_
#define SLIDINGLAWFACTORY_H_

#include <memory>

class SlidingLaw;
class PhysicsConfiguration; // TODO: write this class ...

class SlidingLawFactory
{
public:
	SlidingLawFactory(PhysicsConfiguration* aPhysConf);
	~SlidingLawFactory();

	// factory method
	static SlidingLaw* make();

protected:
	std::unique_ptr<PhysicsConfiguration> _PhysConf;
};

#endif