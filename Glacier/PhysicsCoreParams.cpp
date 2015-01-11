#include "PhysicsCoreParams.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"

namespace N_Glacier {

	PhysicsCoreParams::PhysicsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysicsCoreConf) 
		: ICoreParams(aPhysicsCoreConf)
	{

	}

	PhysicsCoreParams::~PhysicsCoreParams()
	{

	}

	double PhysicsCoreParams::g() const
	{
		return std::stod(m_Parameters.at("g"));
	}

	double PhysicsCoreParams::rho_w() const
	{
		return std::stod(m_Parameters.at("rho_w"));
	}

	double PhysicsCoreParams::rho_i() const
	{
		return std::stod(m_Parameters.at("rho_i"));
	}

}