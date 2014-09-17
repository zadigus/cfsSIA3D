#ifndef ALTITUDESL_H_
#define ALTITUDESL_H_

#include "SlidingLaw.hpp"

class Grid;

class AltitudeSL: public SlidingLaw {
	public:
		AltitudeSL(std::string slFile, Grid& b, int n);
		AltitudeSL(Grid& b, double Z, double C, int n);

		~AltitudeSL();

		void Generate(Grid& b, int n);

		double Z() const { return x(0); } // Zsl, in m
		double C() const { return x(1); } // C, in bar^{-1}*a^{-1/n}, n is Glen's exponent
};

#endif
