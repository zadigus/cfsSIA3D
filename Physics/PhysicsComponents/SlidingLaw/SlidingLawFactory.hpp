#ifndef SLIDINGLAWFACTORY_H_
#define SLIDINGLAWFACTORY_H_

#include <memory>

namespace N_Physics {

	class Component;
	class SlidingLaw;

	class SlidingLawFactory
	{
	public:
		// factory method
		static SlidingLaw* make(Component* aSlidingLaw = nullptr);
	};
}
#endif