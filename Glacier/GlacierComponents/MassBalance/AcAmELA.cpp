#include "AcAmELA.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	AcAmELA::AcAmELA(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component)
		: MassBalance(a_PhysCoreParams, a_Component)
		, m_ELA(std::stod(m_Parameters.at("ELA")))
		, m_ac(std::stod(m_Parameters.at("ac")))
		, m_am(std::stod(m_Parameters.at("am")))
		, m_eps(std::stod(m_Parameters.at("eps")))
	{
		LOG_INF("ELA = " << ELA());
		LOG_INF("ac  = " << ac());
		LOG_INF("am  = " << am());
		LOG_INF("eps = " << eps());
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
