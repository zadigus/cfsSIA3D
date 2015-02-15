#ifndef ZEROSL_H_
#define ZEROSL_H_

#include "AltitudeSL.hpp"

namespace N_Glacier {
	class ZeroSL : public AltitudeSL {
	public:
		ZeroSL();
		virtual ~ZeroSL();

	protected:
		virtual void Stagger(unsigned int a_GlenExp);

	private:
		ZeroSL(const ZeroSL&); // not implemented
		ZeroSL& operator=(const ZeroSL&); // not implemented
	};
}

#endif
