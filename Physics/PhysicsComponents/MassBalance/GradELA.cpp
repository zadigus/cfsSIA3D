#include "GradELA.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Physics {

	GradELA::GradELA(N_Configuration::Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
		: MassBalance(aComponent, aPhysCoreParams)
		, _ELA(std::stod(_parameters["ELA"]))
		, _m1(std::stod(_parameters["m1"]))
		, _m2(std::stod(_parameters["m2"]))
		, _eps(std::stod(_parameters["eps"]))
	{

	}

	GradELA::GradELA() : MassBalance()
	{

	}

	GradELA::~GradELA()
	{

	}

	const double GradELA::operator()(const double x, const double y, const double b, const double H)
	{
		// Only depends on b and H
		return (*this)(b, H, H);
	}

	const double GradELA::operator()(const double b, const double H3, const double H2)
	{ // = B(b, H3, H2)
		return water2ice(N_MathUtils::Heaviside(H2) * ((m1() + m2()) / 2.*(b + H3 - ELA()) - sqrt(((m1() - m2()) / 2.*(b + H3 - ELA()))*((m1() - m2()) / 2.*(b + H3 - ELA())) + eps())));
	}

	double GradELA::dB(double b, double H3, double H2)
	{ // dB/ds, especially useful in routine Climate(), because of the Newton process used for it
		double tmp((m1() - m2())*(m1() - m2()) / 4.*(b + H3 - ELA()));
		if (tmp != 0.0)
			return water2ice(N_MathUtils::Heaviside(H2) * ((m1() + m2()) / 2. - tmp / sqrt(((m1() - m2()) / 2.*(b + H3 - ELA()))*((m1() - m2()) / 2.*(b + H3 - ELA())) + eps())));
		return water2ice(N_MathUtils::Heaviside(H2) * (m1() + m2()) / 2.);
	}

}