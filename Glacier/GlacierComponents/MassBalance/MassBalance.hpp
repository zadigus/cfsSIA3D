#ifndef MASSBALANCE_H_
#define MASSBALANCE_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"
//#include "GlacierComponent.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Glacier { 

	struct PhysicsCoreParams;

	// Interface class for mass-balance data
	class MassBalance : public GlacierComponent {
		public:
			MassBalance(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component);
			MassBalance(const PhysicsCoreParams& a_PhysCoreParams);
			virtual ~MassBalance();

			// Routines to be interfaced
			virtual const double operator()(const double, const double, const double, const double) = 0; // value of _B
			virtual const double operator()(const double, const double, const double) = 0; // value of _B for the Newton method
			virtual double dB(double, double, double) = 0; // derivative of _B for the Newton method

			//
			//void Export(Grid& b, Grid& H, std::string fileName);

			// units transformation: convert quantity Q from meter water equivalent to meter ice equivalent
			double water2ice(double Q) { return Q * m_rho_water / m_rho_ice; } // TODO: double-check that formula

		private:
			MassBalance(const MassBalance&); // not implemented
			MassBalance& operator=(const MassBalance&); // not implemented

		private:
			double m_rho_ice; // ice density
			double m_rho_water; // water density
	};

}
#endif /* MASSBALANCE_H_ */
