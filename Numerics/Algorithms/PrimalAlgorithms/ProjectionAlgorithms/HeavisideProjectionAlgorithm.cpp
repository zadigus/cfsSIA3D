#include "HeavisideProjectionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Math.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

namespace N_Mathematics {

	HeavisideProjectionAlgorithm::HeavisideProjectionAlgorithm(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aProjectionAlgo)
		: FiniteDifferenceProjectionAlgorithm(aProjectionAlgo) 
	{
		// TODO: read further algorithm parameters here
	}

	HeavisideProjectionAlgorithm::~HeavisideProjectionAlgorithm()
	{

	}

  void HeavisideProjectionAlgorithm::transform(N_Glacier::Glacier& a_g)
	{
    for(size_t i(0); i < a_g.Nx(); ++i) // prefix increment operator is more efficient
      for(size_t j(0); j < a_g.Ny(); ++j)
        a_g.H(i, j) = N_MathUtils::Heaviside(a_g.H(i, j)) * a_g.H(i, j);
	}

}
