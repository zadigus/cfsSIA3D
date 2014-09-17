#ifndef ZEROSL_H_
#define ZEROSL_H_

#include "AltitudeSL.hpp"

class Grid;
class Component;

class ZeroSL: public AltitudeSL {
	public:
		ZeroSL(Component* aComponent);
		virtual ~ZeroSL();
		
	protected:
		virtual void Stagger(unsigned int);
};

#endif
