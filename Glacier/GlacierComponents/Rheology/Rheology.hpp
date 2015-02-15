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
		Rheology(const PhysicsCoreParams& aPhysCoreParams, const N_Configuration::Component& aComponent);
		virtual ~Rheology();

		// Setter
		//void Set(unsigned int i, double val);

		// Access to rheological quantities
		double n() { return m_n; } // Glen exponent
		double A(); // rate factor in Pa^{-n}*a^{-1}
		double rhogn() const { return m_rhogn; }
		double Gamma() const { return m_Gamma; }

	protected:
		void UpdateGamma();

	private:
		Rheology(const Rheology&); // not implemented
		Rheology& operator=(const Rheology&); // not implemented

	private:
		double			  m_A; // rate factor [bar^{-n} a^{-1}]
		double				m_n; // Glen exponent [no units]
		double	    m_rho; // ice density [kg/m^3]
		double	      m_g; // gravitational acceleration [m/s^2]
		double    m_rhogn; // (rho*g)^n
		double    m_Gamma; // Gamma = 2A(rho g)^n/(n+2)
	};

}

#endif /* RHEOLOGY_H_ */
