#ifndef CONSTANTSL_H_
#define CONSTANTSL_H_

#include "SlidingLaw.hpp"

class Grid;
//class Component;

namespace N_Physics {

	class ConstantSL : public SlidingLaw {
	public:
		ConstantSL(Component* aComponent);
		~ConstantSL();
		//void Generate(Grid&, int);
	protected:
		virtual void Init(const Grid&);
		//virtual void Fill(Grid&, unsigned int);
	};
}

#endif
