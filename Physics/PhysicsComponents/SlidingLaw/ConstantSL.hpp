#ifndef CONSTANTSL_H_
#define CONSTANTSL_H_

#include "SlidingLaw.hpp"

class Grid;

namespace N_Physics {

	class ConstantSL : public SlidingLaw {
	public:
		ConstantSL(N_Configuration::Component* aComponent);
		~ConstantSL();
	protected:
		virtual void Init(const Grid&);
	};
}

#endif
