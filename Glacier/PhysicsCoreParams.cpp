#include "PhysicsCoreParams.hpp"

#include "Configuration/PhysicsCoreConfiguration.hpp"

namespace N_Glacier {

	PhysicsCoreParams::PhysicsCoreParams(std::unique_ptr<N_Configuration::PhysicsCoreConfiguration>& aPhysicsCoreConf)
	{
		N_Configuration::PhysicsCoreConfiguration::Parameter_sequence paramSeq = aPhysicsCoreConf->Parameter();
		for (N_Configuration::PhysicsCoreConfiguration::Parameter_const_iterator it = paramSeq.begin(); it != paramSeq.end(); it++)
		{
			_parameters.emplace(it->name(), (*it));
		}
	}

	double PhysicsCoreParams::g()
	{
		std::map<std::string, std::string>::iterator it(_parameters.find("g"));
		return it != _parameters.end() ? std::stod(it->second) : 9.81;
	}

	double PhysicsCoreParams::rho_w()
	{
		std::map<std::string, std::string>::iterator it(_parameters.find("rho_w"));
		return it != _parameters.end() ? std::stod(it->second) : 1000;
	}

	double PhysicsCoreParams::rho_i()
	{
		std::map<std::string, std::string>::iterator it(_parameters.find("rho_i"));
		return it != _parameters.end() ? std::stod(it->second) : 910;
	}

}