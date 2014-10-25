#ifndef RHEOLOGY_H_
#define RHEOLOGY_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"

#include <string>
#include <vector>

// Rheology object, namely everything around Gamma, A, n
namespace N_Glacier {

	struct PhysicsCoreParams;

	class Rheology : public GlacierComponent {
	public:
		Rheology(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent = nullptr);
		virtual ~Rheology();

		// Setter
		//void Set(unsigned int i, double val);

		// Access to rheological quantities
		double n() { return _n; } // Glen exponent
		double A(); // rate factor in Pa^{-n}*a^{-1}
		double rhogn() const { return _rhogn; }
		double Gamma() const { return _Gamma; }

	protected:
		void UpdateGamma();

	private:
		double			  _A; // rate factor [bar^{-n} a^{-1}]
		double				_n; // Glen exponent [no units]
		double	    _rho; // ice density [kg/m^3]
		double	      _g; // gravitational acceleration [m/s^2]
		double    _rhogn; // (rho*g)^n
		double    _Gamma; // Gamma = 2A(rho g)^n/(n+2)
	};

}

#endif /* RHEOLOGY_H_ */
