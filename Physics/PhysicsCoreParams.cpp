#include "PhysicsCoreParams.hpp"

#include "PhysicsComponents/PhysicsCoreConfiguration.hpp"

namespace N_Physics {

	PhysicsCoreParams::PhysicsCoreParams(std::unique_ptr<PhysicsCoreConfiguration>& aPhysicsCoreConf)
	{
		PhysicsCoreConfiguration::Parameter_sequence paramSeq = aPhysicsCoreConf->Parameter();
		for (PhysicsCoreConfiguration::Parameter_const_iterator it = paramSeq.begin(); it != paramSeq.end(); it++)
		{
			_parameters.emplace(it->name(), (*it));
		}
	}

	double PhysicsCoreParams::g()
	{
		std::map<std::string, double>::iterator it(_parameters.find("g"));
		return it != _parameters.end() ? it->second : 9.81;
	}

	double PhysicsCoreParams::rho_w()
	{
		std::map<std::string, double>::iterator it(_parameters.find("rho_w"));
		return it != _parameters.end() ? it->second : 1000;
	}

	double PhysicsCoreParams::rho_i()
	{
		std::map<std::string, double>::iterator it(_parameters.find("rho_i"));
		return it != _parameters.end() ? it->second : 910;
	}

}