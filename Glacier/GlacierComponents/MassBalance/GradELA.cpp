#include "GradELA.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	//GradELA::GradELA(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent)
	GradELA::GradELA(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component)
		: MassBalance(a_PhysCoreParams, a_Component)
		, m_ELA(std::stod(m_Parameters.at("ELA")))
		, m_m1(std::stod(m_Parameters.at("m1")))
		, m_m2(std::stod(m_Parameters.at("m2")))
		, m_eps(std::stod(m_Parameters.at("eps")))
	{
		LOG_INF("ELA = " << ELA());
		LOG_INF("m1  = " << m1());
		LOG_INF("m2  = " << m2());
		LOG_INF("eps = " << eps());
	}

	GradELA::GradELA(const PhysicsCoreParams& a_PhysCoreParams)
		: MassBalance(a_PhysCoreParams)
		, m_ELA(0)
		, m_m1(0)
		, m_m2(0)
		, m_eps(0)
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
