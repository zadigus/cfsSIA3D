#ifndef SLIDINGLAWFACTORY_H_
#define SLIDINGLAWFACTORY_H_

#include <memory>

class SlidingLaw;
class Component; 

class SlidingLawFactory
{
public:
	// factory method
	static SlidingLaw* make(Component* aSlidingLaw);
};

#endif