#include "HeavisideProjectionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	HeavisideProjectionAlgorithm::HeavisideProjectionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo)
		: FiniteDifferenceProjectionAlgorithm(aProjectionAlgo) 
	{
		
	}

	HeavisideProjectionAlgorithm::~HeavisideProjectionAlgorithm()
	{

	}

	void HeavisideProjectionAlgorithm::Run()
	{
		for(unsigned int i(0); i < _Nx; ++i) // prefix increment operator is more efficient
			for(unsigned int j(0); j < _Ny; ++j)
				H(i, j) = N_MathUtils::Heaviside(H(i, j)) * H(i, j);
	}

}