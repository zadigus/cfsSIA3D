#include "FiniteDifferencePrimalAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Logger/Logger.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

#include "Numerics/LinSyst/Vector.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferencePrimalAlgorithm::FiniteDifferencePrimalAlgorithm(N_Configuration::Component* aFiniteDifferenceAlgo) 
		: PrimalAlgorithm(aFiniteDifferenceAlgo)
		, m_H(m_glacier.H())
		, m_Nx(m_H->Nx())
		, m_Ny(m_H->Ny())
		, m_Dx(m_H->Dx())
		, m_b(m_glacier.b())
		, m_gradbx(m_glacier.gradbx())
		, m_gradby(m_glacier.gradby())
	{
		//assert(_Dx == _H->Dy()); // TODO: enforce that somewhere else
	}

	FiniteDifferencePrimalAlgorithm::~FiniteDifferencePrimalAlgorithm()
	{

	}

	void FiniteDifferencePrimalAlgorithm::Vector2Grid(const std::shared_ptr<Vector>& aVector, const std::shared_ptr<Grid>& aGrid)
	{
		LOG_WRN("Using default vector to grid conversion.");
		unsigned int I(0);

		for (unsigned int i(0); i < aGrid->Nx(); ++i)   // by default, we go from 0 and end with Nx/Ny
		{
			for (unsigned int j(0); j < aGrid->Ny(); ++j)
			{
				(*aGrid)(i, j) = (*aVector)[I++];
			}
		}
	}

	double& FiniteDifferencePrimalAlgorithm::H(unsigned int i, unsigned int j)
	{
		return (*m_H)(i, j);
	}

	double FiniteDifferencePrimalAlgorithm::b(unsigned int i, unsigned int j)
	{
		return (*m_b)(i, j);
	}

	double FiniteDifferencePrimalAlgorithm::gradbx(unsigned int i, unsigned int j)
	{
		return (*m_gradbx)(i, j);
	}

	double FiniteDifferencePrimalAlgorithm::gradby(unsigned int i, unsigned int j)
	{
		return (*m_gradby)(i, j);
	}

}