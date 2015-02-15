#ifndef ZEROMB_H_
#define ZEROMB_H_

#include "GradELA.hpp"

class Grid;

namespace N_Glacier {

	struct PhysicsCoreParams;

	class ZeroMB : public GradELA {
		public:
			// Constructor / destructor
			ZeroMB(const PhysicsCoreParams& a_PhysCoreParams);
			virtual ~ZeroMB();

		private:
			ZeroMB(const ZeroMB&); // not implemented
			ZeroMB& operator=(const ZeroMB&); // not implemented

	};

}

#endif
