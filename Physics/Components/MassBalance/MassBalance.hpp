#ifndef MASSBALANCE_H_
#define MASSBALANCE_H_

#include "PhysicalComponent.hpp"

class Grid;
class Component;
struct PhysicsCoreParams;

// Interface class for mass-balance data
class MassBalance : public PhysicalComponent {
public:
	MassBalance(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
	virtual ~MassBalance();

	// Routines to be interfaced
	virtual const double operator()(const double, const double, const double, const double) = 0; // value of _B
	virtual const double operator()(const double, const double, const double) = 0; // value of _B for the Newton method
	virtual double dB(double, double, double) = 0; // derivative of _B for the Newton method

	//
	//void Export(Grid& b, Grid& H, std::string fileName);

	// units transformation: convert quantity Q from meter water equivalent to meter ice equivalent
	double water2ice(double Q) { return Q * _rho_water / _rho_ice; } // TODO: double-check that formula

private:
	double _rho_ice; // ice density
	double _rho_water; // water density
};

#endif /* MASSBALANCE_H_ */
