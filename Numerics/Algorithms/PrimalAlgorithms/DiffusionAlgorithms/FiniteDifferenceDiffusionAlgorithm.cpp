#include "FiniteDifferenceDiffusionAlgorithm.hpp"

#include "Utility/Logger/Logger.hpp"
#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Numerics/LinSyst/LinSystFactory.hpp"
#include "Numerics/LinSyst/LinSyst.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceDiffusionAlgorithm::FiniteDifferenceDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo) 
		: FiniteDifferencePrimalAlgorithm(aDiffusionAlgo)
		, m_Rh(m_glacier.Rh())
		, m_Sl(m_glacier.Sl())
		, m_D(new Grid(m_Nx, m_Ny, m_Dx, m_H->Dy()))
		, m_LinSyst(nullptr) 
	{
		//assert(_Dx == _H->Dy()); // TODO: enforce that somewhere else
		if (aDiffusionAlgo)
		{
			N_Configuration::Component::SubComponent_sequence subComponents(aDiffusionAlgo->SubComponent());
			for (N_Configuration::Component::SubComponent_iterator it(subComponents.begin()); it != subComponents.end(); ++it)
			{
				if (!strcmp(it->name()->c_str(), "LinearSystem"))
				{
					LOG_INF("Setting diffusion algorithm's linear system.");
					m_LinSyst.reset(LinSystFactory::make(&(*it)));
				}
			}
		}
	}

	FiniteDifferenceDiffusionAlgorithm::~FiniteDifferenceDiffusionAlgorithm()
	{

	}
	
	double FiniteDifferenceDiffusionAlgorithm::staggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H) 
	{
		// because this function is also used in the FullyImplicit version
		assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < m_Nx); assert(j < m_Ny);
		return sqrt((b(i, j    ) + (*H)(i, j    ) - b(i - 1, j - 1) - (*H)(i - 1, j - 1))*(b(i, j    ) + (*H)(i, j    ) - b(i - 1, j - 1) - (*H)(i - 1, j - 1))
							+ (b(i, j - 1) + (*H)(i, j - 1) - b(i - 1, j    ) - (*H)(i - 1, j    ))*(b(i, j - 1) + (*H)(i, j - 1) - b(i - 1, j    ) - (*H)(i - 1, j    ))) / (sqrt(2)*m_Dx);
	}

	double& FiniteDifferenceDiffusionAlgorithm::D(unsigned int i, unsigned int j)
	{
		return (*m_D)(i, j);
	}

	double FiniteDifferenceDiffusionAlgorithm::Gamma()
	{
		return m_Rh->Gamma();
	}

	double FiniteDifferenceDiffusionAlgorithm::rhogn()
	{
		return m_Rh->rhogn();
	}

	double FiniteDifferenceDiffusionAlgorithm::n()
	{
		return m_Rh->n();
	}

	double FiniteDifferenceDiffusionAlgorithm::Sl(unsigned int i, unsigned int j)
	{
		return (*m_Sl)(i, j);
	}

	void FiniteDifferenceDiffusionAlgorithm::solveLinSyst()
	{
		m_LinSyst->solve();
	}

	void FiniteDifferenceDiffusionAlgorithm::updateThickness()
	{
		Vector2Grid(m_LinSyst->getSolution(), m_H);
	}

	void FiniteDifferenceDiffusionAlgorithm::run()
	{
		fillLinSyst();
		solveLinSyst();
		updateThickness();
	}

}