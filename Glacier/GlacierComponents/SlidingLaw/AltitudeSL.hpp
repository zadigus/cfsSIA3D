#ifndef ALTITUDESL_H_
#define ALTITUDESL_H_

#include "SlidingLaw.hpp"

class Grid;

namespace N_Glacier {

	class AltitudeSL : public SlidingLaw {
	public:
		AltitudeSL(N_Configuration::Component* aComponent = nullptr);
		virtual ~AltitudeSL();

	protected:
		virtual void Fill(Grid& fs, unsigned int n);
		virtual double Z() { return m_Z; }
		virtual double C() { return m_C; }

	protected:
		double m_Z; // Zsl, in m
		double m_C; // C, in bar^{-1}*a^{-1/n}, n is Glen's exponent

	};
}

#endif
