#ifndef ACAMELA_H_
#define ACAMELA_H_

#include "MassBalance.hpp"

namespace N_Physics {

	//class Component;
	struct PhysicsCoreParams;

	class AcAmELA : public MassBalance {
		public:
			// Constructor / destructor
			AcAmELA(N_Configuration::Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
			virtual ~AcAmELA();

			virtual const double operator()(const double x, const double y, const double b, const double H);

			// Function values for Newton method
			virtual const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
			virtual double dB(double b, double H3, double H2); // dBdH(b, Hn, H)

		protected:
			double ELA() { return _ELA; }
			double  ac() { return _ac; }
			double  am() { return _am; }
			double eps() { return _eps; }

		protected:
			double _ELA;
			double  _ac;
			double  _am;
			double _eps;
	};

}

#endif