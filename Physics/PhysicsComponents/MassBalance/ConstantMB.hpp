#ifndef CONSTANTMB_H_
#define CONSTANTMB_H_

#include "MassBalance.hpp"

class Grid;

namespace N_Physics {

	struct PhysicsCoreParams;

	class ConstantMB : public MassBalance {
	public:
		// Constructor / destructor
		ConstantMB(N_Configuration::Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
		virtual ~ConstantMB();

		const double operator()(const double x, const double y, const double b, const double H);

		// Function values for Newton method
		const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
		double dB(double b, double H3, double H2); // dBdH(b, Hn, H)

	protected:
		std::unique_ptr<Grid> _mb;
	};

}

#endif