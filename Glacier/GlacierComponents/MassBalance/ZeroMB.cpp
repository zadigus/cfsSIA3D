#include "ZeroMB.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	ZeroMB::ZeroMB(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
		: GradELA(aPhysCoreParams)
	{
		// the parameters are not defined in the map, hence set to zero by default
	}

	ZeroMB::~ZeroMB()
	{

	}

}