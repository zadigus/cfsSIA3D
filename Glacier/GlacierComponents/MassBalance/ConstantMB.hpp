#ifndef CONSTANTMB_H_
#define CONSTANTMB_H_

#include "MassBalance.hpp"

class Grid;

namespace N_Glacier {

	struct PhysicsCoreParams;

	class ConstantMB : public MassBalance {
		public:
			// Constructor / destructor
			ConstantMB(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component);
			virtual ~ConstantMB();

			const double operator()(const double x, const double y, const double b, const double H);

			// Function values for Newton method
			const double operator()(const double b, const double H3, const double H2); // B(b, Hn, H)
			double dB(double b, double H3, double H2); // dBdH(b, Hn, H)

		private:
			ConstantMB(const ConstantMB&); // not implemented
			ConstantMB& operator=(const ConstantMB&); // not implemented

		protected:
			std::unique_ptr<Grid> m_mb;
	};

}

#endif
