#include "FullyImplicitClimateAlgorithm.hpp"

#include <functional>

#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

using namespace std::placeholders;

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aClimateAlgo)
		: FiniteDifferenceClimateAlgorithm(aClimateAlgo)
		, m_Hn(new Grid(*m_H)) // initialization of Newton process
		, m_err(1)
		, m_updt(0) 
		, m_F(0) 
		, m_Fp(0) 
		, m_dt(aNumCoreParams.dt())
	{
		N_Configuration::Component::SubComponent_sequence subComponents(aClimateAlgo.SubComponent());
		N_Configuration::Component::SubComponent_iterator it(std::find_if(subComponents.begin(), subComponents.end(), IsSubComponent("Newton")));
		if (it != subComponents.end())
		{
			N_Configuration::SubComponent::Parameter_sequence  params(it->Parameter());
			std::for_each(params.begin(), params.end(), std::bind(&FullyImplicitClimateAlgorithm::setParameter, this, _1));
		}

		m_tol = m_Parameters.find("tol") != m_Parameters.end() ? std::stod(m_Parameters["tol"]) : 1e-6;

	}

	FullyImplicitClimateAlgorithm::~FullyImplicitClimateAlgorithm()
	{

	}

	void FullyImplicitClimateAlgorithm::run()
	{
		while (m_err > m_tol) {
			m_err = 0;
			for (unsigned int i(0); i<m_Nx; ++i) {
				for (unsigned int j(0); j<m_Ny; ++j) {
					// TODO: integrate constantMB; it should be possible to access B with x, y too
					m_F = Hn(i, j) - H(i, j) - m_dt*(*m_B)(b(i, j), Hn(i, j), H(i, j));  // TODO: access through glacier member -> no need to give b and H any more; find a solution for Hn
					m_Fp = 1 - m_dt*m_B->dB(b(i, j), Hn(i, j), H(i, j)); // derivative of mass balance wrt glacier surface
					m_updt = m_F / m_Fp; Hn(i, j) -= m_updt;
					if (fabs(m_updt) > m_err) m_err = fabs(m_updt);
				}
			}
		}

		*m_H = *m_Hn;
	}

	double& FullyImplicitClimateAlgorithm::Hn(unsigned int i, unsigned int j)
	{
		return (*m_Hn)(i, j);
	}

}