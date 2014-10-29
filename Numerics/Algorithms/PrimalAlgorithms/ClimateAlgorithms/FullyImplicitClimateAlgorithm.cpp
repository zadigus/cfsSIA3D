#include "FullyImplicitClimateAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo)
		: FiniteDifferenceClimateAlgorithm(aClimateAlgo)
		, m_Hn(new Grid(*m_H)) // initialization of Newton process
		, m_err(1)
		//, m_tol(m_parameters.find("tol") != m_parameters.end() ? std::stod(m_parameters["tol"]) : 1e-6)
		, m_updt(0) 
		, m_F(0) 
		, m_Fp(0) 
		, m_dt(aNumCoreParams->dt())
	{
		if (aClimateAlgo)
		{
			N_Configuration::Component::SubComponent_sequence subComponents(aClimateAlgo->SubComponent());
			for (N_Configuration::Component::SubComponent_const_iterator it(subComponents.begin()); it != subComponents.end(); ++it)
			{
				if (!strcmp(it->name()->c_str(), "Newton"))
				{
					N_Configuration::SubComponent::Parameter_sequence  params(it->Parameter());
					for (N_Configuration::SubComponent::Parameter_const_iterator it(params.begin()); it != params.end(); ++it)
					{
						m_parameters.emplace(it->name(), (*it));
					}
				}
			}
		}

		m_tol = m_parameters.find("tol") != m_parameters.end() ? std::stod(m_parameters["tol"]) : 1e-6;

	}

	FullyImplicitClimateAlgorithm::~FullyImplicitClimateAlgorithm()
	{

	}

	void FullyImplicitClimateAlgorithm::Run()
	{
		while (m_err > m_tol) {
			m_err = 0;
			for (unsigned int i(0); i<m_Nx; ++i) {
				for (unsigned int j(0); j<m_Ny; ++j) { // TODO: try to write that as a linear system?
					// TODO: integrate constantMB; it should be possible to access B with x, y too
					m_F = Hn(i, j) - H(i, j) - m_dt*(*m_B)(b(i, j), Hn(i, j), H(i, j)); 
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