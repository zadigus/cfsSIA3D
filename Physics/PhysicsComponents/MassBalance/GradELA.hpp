#ifndef GRADELA_H_
#define GRADELA_H_

#include "MassBalance.hpp"

namespace N_Physics {

	//class Component;
	struct PhysicsCoreParams;

	class GradELA : public MassBalance {
	public:
		// Constructor / destructor
		GradELA(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
		GradELA();
		virtual ~GradELA();

		// Getters
		double ELA(){ return _parameters["ELA"]; } // equilibrium line altitude
		double m1() { return _parameters["m1"]; }  // melting rate below ELA
		double m2() { return _parameters["m2"]; }  // melting rate above ELA; m2<=m1
		double eps(){ return _parameters["eps"]; } // regularization parameter

		virtual const double operator()(const double x, const double y, const double b, const double H);

		// Derivatives of B for Newton method
		virtual const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
		virtual double dB(double b, double H3, double H2); // dBdH(b, Hn, H)
	};

}

#endif