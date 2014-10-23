#include "FiniteDifferenceDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Numerics/LinSyst/LinSyst.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceDiffusionAlgorithm::FiniteDifferenceDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo) 
		: PrimalAlgorithm(aDiffusionAlgo)
		, _b(N_Glacier::Glacier::getInstance()->b())
		, _H(N_Glacier::Glacier::getInstance()->H())
		, _Rh(N_Glacier::Glacier::getInstance()->Rh())
		, _Sl(N_Glacier::Glacier::getInstance()->Sl())
		, _Nx(_H->Nx())
		, _Ny(_H->Ny())
		, _Dx(_H->Dx())
		, _LinSyst(new LinSyst(_Nx*_Ny)) // TODO: give the Component's parameters too? 
	{
		assert(_Dx == _H->Dy());
	}

	FiniteDifferenceDiffusionAlgorithm::~FiniteDifferenceDiffusionAlgorithm()
	{

	}

	double FiniteDifferenceDiffusionAlgorithm::StaggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H) {
		// because this function is also used in the FullyImplicit version
		assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < _Nx); assert(j < _Ny);
		return sqrt(((*_b)(i, j) + (*H)(i, j) - (*_b)(i - 1, j - 1) - (*H)(i - 1, j - 1))*((*_b)(i, j) + (*H)(i, j) - (*_b)(i - 1, j - 1) - (*H)(i - 1, j - 1))
			+ ((*_b)(i, j - 1) + (*H)(i, j - 1) - (*_b)(i - 1, j) - (*H)(i - 1, j))*((*_b)(i, j - 1) + (*H)(i, j - 1) - (*_b)(i - 1, j) - (*H)(i - 1, j))) / (sqrt(2)*_Dx);
	}

}