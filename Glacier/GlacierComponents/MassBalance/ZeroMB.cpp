#include "ZeroMB.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	ZeroMB::ZeroMB(const PhysicsCoreParams& a_PhysCoreParams)
		: GradELA(a_PhysCoreParams)
	{
		// the parameters are not defined in the map, hence set to zero by default
	}

	ZeroMB::~ZeroMB()
	{

	}

}
