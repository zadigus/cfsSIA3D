#include "PhysicsCoreParams.hpp"

#include "Utility/Logger/Logger.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"

namespace N_Glacier {

	PhysicsCoreParams::PhysicsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysicsCoreConf)
	{
		if (!aPhysicsCoreConf)
		{
			LOG_ERR("Physics core configuration not specified.");
			exit(EXIT_FAILURE);
		}

		N_Configuration::ModelCoreConfiguration::Parameter_sequence paramSeq = aPhysicsCoreConf->Parameter();
		for (N_Configuration::ModelCoreConfiguration::Parameter_const_iterator it = paramSeq.begin(); it != paramSeq.end(); ++it)
		{
			m_parameters.emplace(it->name(), (*it));
		}
	}

	double PhysicsCoreParams::g() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("g"));
		return it != m_parameters.end() ? std::stod(it->second) : 9.81;
	}

	double PhysicsCoreParams::rho_w() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("rho_w"));
		return it != m_parameters.end() ? std::stod(it->second) : 1000;
	}

	double PhysicsCoreParams::rho_i() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("rho_i"));
		return it != m_parameters.end() ? std::stod(it->second) : 910;
	}

}