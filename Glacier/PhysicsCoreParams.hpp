#ifndef PHYSICSCOREPARAMS_H_
#define PHYSICSCOREPARAMS_H_

#include "Utility/ICoreParams.hpp"

namespace N_Glacier {

	struct PhysicsCoreParams : public ICoreParams
	{
		PhysicsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aPhysicsCoreConf);
		virtual ~PhysicsCoreParams();

		double g()     const; // gravitational acceleration [m/s^2]
		double rho_i() const; // ice density [kg/m^3]
		double rho_w() const; // water density [kg/m^3]
	};

}

#endif