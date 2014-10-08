#include "HeavisideProjectionAlgorithm.hpp"

#include "Numerics/Mesh/Grid.hpp"
#include "Utility/Math.hpp"

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	HeavisideProjectionAlgorithm::HeavisideProjectionAlgorithm(N_Configuration::Component* aProjectionAlgo) //, std::shared_ptr<N_Glacier::Glacier>& aGlacier)
		: PrimalAlgorithm(aProjectionAlgo) //, aGlacier)
	{

	}

	HeavisideProjectionAlgorithm::~HeavisideProjectionAlgorithm()
	{

	}

	void HeavisideProjectionAlgorithm::Run()
	{
		// TODO: UPDATE THAT FUNCTION
		for(unsigned int i(0); i < _H->Nx(); ++i) // prefix increment operator is more efficient
			for(unsigned int j(0); j < _H->Ny(); ++j)
				(*_H)(i, j) = N_MathUtils::Heaviside((*_H)(i, j)) * (*_H)(i, j);
	}

}