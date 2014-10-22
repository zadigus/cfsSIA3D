#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo) 
		: PrimalAlgorithm(aDiffusionAlgo)
		, _b(N_Glacier::Glacier::getInstance()->b())
		, _H(N_Glacier::Glacier::getInstance()->H())
		, _Rh(N_Glacier::Glacier::getInstance()->Rh())
		, _Sl(N_Glacier::Glacier::getInstance()->Sl())
		, _Nx(_H->Nx())
		, _Ny(_H->Ny())
		, _Dx(_H->Dx())
	{
		assert(_Dx == _H->Dy());
	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
	
	}

	void SemiImplicitDiffusionAlgorithm::Diffusivity() {
		double c1(0.), c2(0.);
		double Gamma(_Rh->Gamma()), rhogn(_Rh->rhogn()), n(_Rh->n());
		for (unsigned int i = 1; i<_Nx; i++) {
			for (unsigned int j = 1; j<_Ny; j++) {
				c1 = _H->Staggered(i, j);
				c2 = StaggeredGradSurfNorm(i, j);
				(*_D)(i, j) = (Gamma*c1 + rhogn*(*_Sl)(i, j)) * pow(c1, n + 1)*pow(c2, n - 1);
			}
		}
	}

	double SemiImplicitDiffusionAlgorithm::StaggeredGradSurfNorm(unsigned int i, unsigned int j) { // TODO: let this function depend on a thickness; write a base class that implements this routine
		// because this function is also used in the FullyImplicit version
		assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < _Nx); assert(j < _Ny);
		return sqrt(((*_b)(i, j) + (*_H)(i, j) - (*_b)(i - 1, j - 1) - (*_H)(i - 1, j - 1))*((*_b)(i, j) + (*_H)(i, j) - (*_b)(i - 1, j - 1) - (*_H)(i - 1, j - 1))
			+ ((*_b)(i, j - 1) + (*_H)(i, j - 1) - (*_b)(i - 1, j) - (*_H)(i - 1, j))*((*_b)(i, j - 1) + (*_H)(i, j - 1) - (*_b)(i - 1, j) - (*_H)(i - 1, j))) / (sqrt(2)*_Dx);
	}

}