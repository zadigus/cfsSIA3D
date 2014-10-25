#include "FiniteDifferencePrimalAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferencePrimalAlgorithm::FiniteDifferencePrimalAlgorithm(/*const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, */N_Configuration::Component* aFiniteDifferenceAlgo) 
		: PrimalAlgorithm(aFiniteDifferenceAlgo)
		, _b(N_Glacier::Glacier::getInstance()->b())
		, _H(N_Glacier::Glacier::getInstance()->H())
		
		, _Nx(_H->Nx())
		, _Ny(_H->Ny())
		, _Dx(_H->Dx())
	{
		//assert(_Dx == _H->Dy()); // TODO: enforce that somewhere else
	}

	FiniteDifferencePrimalAlgorithm::~FiniteDifferencePrimalAlgorithm()
	{

	}

	double& FiniteDifferencePrimalAlgorithm::H(unsigned int i, unsigned int j)
	{
		return (*_H)(i, j);
	}

	double& FiniteDifferencePrimalAlgorithm::b(unsigned int i, unsigned int j)
	{
		return (*_b)(i, j);
	}

}