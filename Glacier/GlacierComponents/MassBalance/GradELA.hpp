#ifndef GRADELA_H_
#define GRADELA_H_

#include "MassBalance.hpp"

namespace N_Glacier {

	struct PhysicsCoreParams;

	class GradELA : public MassBalance {
		public:
			// Constructor / destructor
			GradELA(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component);
			GradELA(const PhysicsCoreParams& a_PhysCoreParams);
			virtual ~GradELA();

			// Getters
			double ELA(){ return m_ELA; } 
			double m1() { return m_m1; }  
			double m2() { return m_m2; }  
			double eps(){ return m_eps; } 

			virtual const double operator()(const double x, const double y, const double b, const double H);

			// Derivatives of B for Newton method
			virtual const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
			virtual double dB(double b, double H3, double H2); // dBdH(b, Hn, H)

		private:
			GradELA(const GradELA&); // not implemented
			GradELA& operator=(const GradELA&); // not implemented

		protected:
			double m_ELA; // equilibrium line altitude [m]
			double  m_m1; // melting rate below ELA [w.e. / a]
			double  m_m2; // melting rate above ELA; m2<=m1 [w.e. / a]
			double m_eps; // regularization parameter
	};

}

#endif
