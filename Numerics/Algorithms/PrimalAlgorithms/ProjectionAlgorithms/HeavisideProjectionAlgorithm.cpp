#include "HeavisideProjectionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

namespace N_Mathematics {

	HeavisideProjectionAlgorithm::HeavisideProjectionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo)
		: FiniteDifferenceProjectionAlgorithm(aProjectionAlgo) 
	{
		
	}

	HeavisideProjectionAlgorithm::~HeavisideProjectionAlgorithm()
	{

	}

	void HeavisideProjectionAlgorithm::run()
	{
		for(unsigned int i(0); i < m_Nx; ++i) // prefix increment operator is more efficient
			for(unsigned int j(0); j < m_Ny; ++j)
				H(i, j) = N_MathUtils::Heaviside(H(i, j)) * H(i, j);
	}

}