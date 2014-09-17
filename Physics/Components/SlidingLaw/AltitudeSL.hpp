#ifndef ALTITUDESL_H_
#define ALTITUDESL_H_

#include "SlidingLaw.hpp"

class Grid;
class Component;

class AltitudeSL: public SlidingLaw {
	public:
		//AltitudeSL(std::string slFile, Grid& b, int n);
		//AltitudeSL(Grid& b, double Z, double C, int n);
		AltitudeSL(Component* aComponent);
		virtual ~AltitudeSL();

		//void Generate(Grid& b, int n);

		double Z() { return _parameters["Z"]; } // Zsl, in m
		double C() { return _parameters["C"]; } // C, in bar^{-1}*a^{-1/n}, n is Glen's exponent

	protected:
		virtual void Fill(Grid& fs, unsigned int n);

};

#endif
