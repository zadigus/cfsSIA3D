#ifndef ALTITUDESL_H_
#define ALTITUDESL_H_

#include "SlidingLaw.hpp"

class Grid;

namespace N_Physics {

	class AltitudeSL : public SlidingLaw {
	public:
		AltitudeSL(N_Configuration::Component* aComponent);
		AltitudeSL();
		virtual ~AltitudeSL();

	protected:
		virtual void Fill(Grid& fs, unsigned int n);
		virtual double Z() { return _Z; }
		virtual double C() { return _C; }

	protected:
		double _Z; // Zsl, in m
		double _C; // C, in bar^{-1}*a^{-1/n}, n is Glen's exponent

	};
}

#endif
