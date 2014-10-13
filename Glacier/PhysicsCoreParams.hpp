#ifndef PHYSICSCOREPARAMS_H_
#define PHYSICSCOREPARAMS_H_

#include <memory>
#include <map>
#include <string>

namespace N_Configuration {
	class PhysicsCoreConfiguration;
}

namespace N_Glacier {

	struct PhysicsCoreParams
	{
		PhysicsCoreParams(const std::unique_ptr<N_Configuration::PhysicsCoreConfiguration>& aPhysicsCoreConf);

		double g();     // gravitational acceleration [m/s^2]
		double rho_i(); // ice density [kg/m^3]
		double rho_w(); // water density [kg/m^3]

		std::map<std::string, std::string> _parameters;
	};

}

#endif