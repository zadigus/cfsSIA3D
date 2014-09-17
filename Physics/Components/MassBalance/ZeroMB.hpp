#ifndef ZEROMB_H_
#define ZEROMB_H_

#include "GradELA.hpp"

class Component;
class Grid;
struct PhysicsCoreParams;

class ZeroMB : public GradELA {
public:
	// Constructor / destructor
	ZeroMB(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
	virtual ~ZeroMB();

	/*const double operator()(const double x, const double y, const double b, const double H);

	// Function values for Newton method
	const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
	double dB(double b, double H3, double H2); // dBdH(b, Hn, H)*/
};

#endif