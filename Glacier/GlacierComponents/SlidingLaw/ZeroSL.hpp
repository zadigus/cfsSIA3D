#ifndef ZEROSL_H_
#define ZEROSL_H_

#include "AltitudeSL.hpp"

class Grid;

namespace N_Glacier {
	class ZeroSL : public AltitudeSL {
	public:
		ZeroSL();
		virtual ~ZeroSL();

	protected:
		virtual void Stagger(unsigned int);
	};
}

#endif
