#ifndef GRADELA_H_
#define GRADELA_H_

#include "MassBalance.hpp"

namespace N_Glacier {

	//class Component;
	struct PhysicsCoreParams;

	class GradELA : public MassBalance {
		public:
			// Constructor / destructor
			//GradELA(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent = nullptr);
			GradELA(const PhysicsCoreParams& aPhysCoreParams, const N_Configuration::Component& aComponent);
			GradELA(const PhysicsCoreParams& aPhysCoreParams);
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
		protected:
			double m_ELA; // equilibrium line altitude [m]
			double  m_m1; // melting rate below ELA [w.e. / a]
			double  m_m2; // melting rate above ELA; m2<=m1 [w.e. / a]
			double m_eps; // regularization parameter
	};

}

#endif