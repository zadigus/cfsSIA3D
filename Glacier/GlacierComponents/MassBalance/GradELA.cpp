#include "GradELA.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	GradELA::GradELA(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent)
		: MassBalance(aPhysCoreParams, aComponent)
		, m_ELA(m_parameters.find("ELA") != m_parameters.end() ? std::stod(m_parameters["ELA"]) : 0)
		, m_m1(m_parameters.find("m1") != m_parameters.end() ? std::stod(m_parameters["m1"]) : 0)
		, m_m2(m_parameters.find("m2") != m_parameters.end() ? std::stod(m_parameters["m2"]) : 0)
		, m_eps(m_parameters.find("eps") != m_parameters.end() ? std::stod(m_parameters["eps"]) : 0)
	{
		LOG_INF("ELA = " << ELA());
		LOG_INF("m1  = " << m1());
		LOG_INF("m2  = " << m2());
		LOG_INF("eps = " << eps());
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