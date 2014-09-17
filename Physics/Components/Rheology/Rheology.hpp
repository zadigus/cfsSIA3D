#ifndef RHEOLOGY_H_
#define RHEOLOGY_H_

#include "PhysicalComponent.hpp"

#include <string>
#include <vector>

// Rheology object, namely everything around Gamma, A, n

struct PhysicsCoreParams;

class Rheology : public PhysicalComponent {
public:
	Rheology(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
	virtual ~Rheology();

	// Setter
	//void Set(unsigned int i, double val);

	// Access to rheological quantities
	double n() { return _parameters["n"]; } // Glen exponent
	double A(); // rate factor; transform A from bar^{-n}*a^{-1} to Pa^{-n}*a^{-1}
	double rhogn() const { return _rhogn; }
	double Gamma() const { return _Gamma; }

protected:
	void UpdateGamma(); 

private:
	double	    _rho; // ice density [kg/m^3]
	double	      _g; // gravitational acceleration [m/s^2]
	double    _rhogn; // (rho*g)^n
	double    _Gamma; // Gamma = 2A(rho g)^n/(n+2)
};

#endif /* RHEOLOGY_H_ */
