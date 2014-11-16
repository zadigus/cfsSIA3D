#include "ConstantMB.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	ConstantMB::ConstantMB(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent)
		: MassBalance(aPhysCoreParams, aComponent)
		, m_mb(new Grid(m_parameters["grid"])) 
	{
		LOG_INF("Grid file name " << m_parameters["grid"]);
	}

	ConstantMB::~ConstantMB()
	{

	}

	const double ConstantMB::operator()(const double x, const double y, const double b, const double H)
	{
		// only depends on surface altitude
		return (*m_mb)(x, y);
	}

	const double ConstantMB::operator()(const double b, const double H3, const double H2)
	{
		return water2ice(0); // TODO: write this right; it must be the value of B at the position (x, y)
	}

	double ConstantMB::dB(double b, double H3, double H2)
	{
		return 0;
	}

}