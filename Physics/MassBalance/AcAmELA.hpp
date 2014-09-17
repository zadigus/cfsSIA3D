#ifndef ACAMELA_H_
#define ACAMELA_H_

#include "MassBalance.hpp"

class Component;

class AcAmELA : public MassBalance {
public:
	// Constructor / destructor
	AcAmELA(Component* aComponent);
	virtual ~AcAmELA();

	// Getters
	double ELA() { return _parameters["ELA"]; }
	double  ac() { return _parameters["ac"]; }
	double  am() { return _parameters["am"]; }
	double eps() { return _parameters["eps"]; }

	virtual const double operator()(const double x, const double y, const double b, const double H);

	// Function values for Newton method
	virtual const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
	virtual double dB(double b, double H3, double H2); // dBdH(b, Hn, H)
};

#endif