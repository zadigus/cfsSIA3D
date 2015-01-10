#ifndef ZEROMB_H_
#define ZEROMB_H_

#include "GradELA.hpp"

class Grid;

namespace N_Glacier {

	struct PhysicsCoreParams;

	class ZeroMB : public GradELA {
	public:
		// Constructor / destructor
		//ZeroMB(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams);
		ZeroMB(const PhysicsCoreParams& aPhysCoreParams);
		virtual ~ZeroMB();
	};

}

#endif