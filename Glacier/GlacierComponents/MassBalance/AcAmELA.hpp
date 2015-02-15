#ifndef ACAMELA_H_
#define ACAMELA_H_

#include "MassBalance.hpp"

namespace N_Glacier {

	struct PhysicsCoreParams;

	class AcAmELA : public MassBalance {
		public:
			// Constructor / destructor
			AcAmELA(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component);
			virtual ~AcAmELA();

			virtual const double operator()(const double x, const double y, const double b, const double H);

			// Function values for Newton method
			virtual const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
			virtual double dB(double b, double H3, double H2); // dBdH(b, Hn, H)

		protected:
			double ELA() { return m_ELA; }
			double  ac() { return m_ac; }
			double  am() { return m_am; }
			double eps() { return m_eps; }

		private:
			AcAmELA(const AcAmELA&); // not implemented
			AcAmELA& operator=(const AcAmELA&); // not implemented

		protected:
			double m_ELA;
			double  m_ac;
			double  m_am;
			double m_eps;
	};

}

#endif
