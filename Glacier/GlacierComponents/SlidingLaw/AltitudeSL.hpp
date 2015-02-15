#ifndef ALTITUDESL_H_
#define ALTITUDESL_H_

#include "SlidingLaw.hpp"

namespace N_Glacier {

	class AltitudeSL : public SlidingLaw {
	public:
		AltitudeSL(const N_Configuration::Component& a_Component);
		AltitudeSL();
		virtual ~AltitudeSL();

	protected:
		virtual void Fill(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp);
		virtual double Z() { return m_Z; }
		virtual double C() { return m_C; }

	private:
		AltitudeSL(const AltitudeSL&); // not implemented
		AltitudeSL& operator=(const AltitudeSL&); // not implemented

	protected:
		double m_Z; // Zsl, in m
		double m_C; // C, in bar^{-1}*a^{-1/n}, n is Glen's exponent

	};
}

#endif
