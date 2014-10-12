#ifndef CONSTANTSL_H_
#define CONSTANTSL_H_

#include "SlidingLaw.hpp"

class Grid;

namespace N_Glacier {

	class ConstantSL : public SlidingLaw {
	public:
		ConstantSL(N_Configuration::Component* aComponent = nullptr);
		~ConstantSL();
	protected:
		virtual void Init(const Grid&);
	};
}

#endif
