#include "AcAmELA.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Physics {

	AcAmELA::AcAmELA(N_Configuration::Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
		: MassBalance(aComponent, aPhysCoreParams)
		, _ELA(std::stod(_parameters["ELA"]))
		, _ac(std::stod(_parameters["ac"]))
		, _am(std::stod(_parameters["am"]))
		, _eps(std::stod(_parameters["eps"]))
	{
	
	}

	AcAmELA::~AcAmELA()
	{

	}

	const double AcAmELA::operator()(const double x, const double y, const double b, const double H)
	{
		// only depends on surface altitude
		return (*this)(b, H, H);
	}

	const double AcAmELA::operator()(const double b, const double H3, const double H2)
	{
		return water2ice(N_MathUtils::Heaviside(H2) * (am() / 2.*(b + H3 - ELA()) + ac() / 2. - sqrt((am() / 2.*(b + H3 - ELA()) - ac() / 2.)*(am() / 2.*(b + H3 - ELA()) - ac() / 2.) + eps())));
	}

	double AcAmELA::dB(double b, double H3, double H2)
	{
		double tmp(am() / 2.*(am() / 2.*(b + H3 - ELA()) - ac() / 2.));
		if (tmp != 0.0)
			return water2ice(N_MathUtils::Heaviside(H2) * (am() / 2. - tmp / sqrt((am() / 2.*(b + H3 - ELA()) - ac() / 2.)*(am() / 2.*(b + H3 - ELA()) - ac() / 2.) + eps())));
		return water2ice(N_MathUtils::Heaviside(H2) * am() / 2.);
	}

}