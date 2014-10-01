#ifndef PHYSICSCOREPARAMS_H_
#define PHYSICSCOREPARAMS_H_

#include <memory>
#include <map>
#include <string>

namespace N_Physics {

	class PhysicsCoreConfiguration;

	struct PhysicsCoreParams
	{
		PhysicsCoreParams(std::unique_ptr<PhysicsCoreConfiguration>& aPhysicsCoreConf);

		double g();     // gravitational acceleration [m/s^2]
		double rho_i(); // ice density [kg/m^3]
		double rho_w(); // water density [kg/m^3]

		std::map<std::string, std::string> _parameters;
	};

}

#endif