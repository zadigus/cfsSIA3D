#ifndef SLIDINGLAWFACTORY_H_
#define SLIDINGLAWFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {

	class SlidingLaw;

	class SlidingLawFactory
	{
	public:
		// factory method
		//static SlidingLaw* make(N_Configuration::Component* aSlidingLaw = nullptr);
		static SlidingLaw* make(const N_Configuration::Component& aSlidingLaw);
		static SlidingLaw* make();
	};
}
#endif