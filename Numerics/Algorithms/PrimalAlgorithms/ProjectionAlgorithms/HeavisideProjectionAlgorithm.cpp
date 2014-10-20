#include "HeavisideProjectionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Math.hpp"
#include "Glacier/Glacier.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	HeavisideProjectionAlgorithm::HeavisideProjectionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aProjectionAlgo)
		: PrimalAlgorithm(aProjectionAlgo) 
		, _H(_glacier->H())
	{
		
	}

	HeavisideProjectionAlgorithm::~HeavisideProjectionAlgorithm()
	{

	}

	void HeavisideProjectionAlgorithm::Run()
	{
		for(unsigned int i(0); i < _H->Nx(); ++i) // prefix increment operator is more efficient
			for(unsigned int j(0); j < _H->Ny(); ++j)
				(*_H)(i, j) = N_MathUtils::Heaviside((*_H)(i, j)) * (*_H)(i, j);
	}

}