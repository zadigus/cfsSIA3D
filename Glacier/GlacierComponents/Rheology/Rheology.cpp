#include "Rheology.hpp"
#include <cmath>
#include <cassert>
#include "PhysicsCoreParams.hpp"

//#include <iostream>

namespace N_Glacier {

	//Rheology::Rheology(const std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent)
	Rheology::Rheology(const PhysicsCoreParams& aPhysCoreParams, const N_Configuration::Component& aComponent)
		: GlacierComponent(aComponent)
		, m_A(m_parameters.find("A") != m_parameters.end() ? std::stod(m_parameters["A"]) : 0)
		, m_n(m_parameters.find("n") != m_parameters.end() ? std::stod(m_parameters["n"]) : 0)
		, m_rho(aPhysCoreParams.rho_i())
		, m_g(aPhysCoreParams.g())
	{

		m_rhogn = pow(m_rho*m_g, n());
		UpdateGamma();
		assert(0 < n() && n() <= 3);
	}

	Rheology::~Rheology()
	{

	}

	void Rheology::UpdateGamma()
	{ // Gamma in consistent units
		m_Gamma = 2 * A() *m_rhogn / (n() + 2);
	}

	double Rheology::A()
	{
		return m_A * pow(1e-5, n());
	}

}

//void Rheology::Set(unsigned int i, double val) {
	//_x[i] = val;
	//if (i == 1) UpdateGamma(); // if A changes, then also Gamma
//}
