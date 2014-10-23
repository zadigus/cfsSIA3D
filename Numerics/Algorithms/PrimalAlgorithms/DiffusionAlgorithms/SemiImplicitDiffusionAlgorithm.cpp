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
		: FiniteDifferenceDiffusionAlgorithm(aNumCoreParams, aDiffusionAlgo)
		, _D(new Grid(_Nx, _Ny, _Dx, _H->Dy(), _H->Xll(), _H->Yll()))
	{
		
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
		for (unsigned int i = 1; i<_Nx; ++i) {
			for (unsigned int j = 1; j<_Ny; ++j) {
				c1 = _H->Staggered(i, j);
				c2 = StaggeredGradSurfNorm(i, j, _H);
				(*_D)(i, j) = (Gamma*c1 + rhogn*(*_Sl)(i, j)) * pow(c1, n + 1)*pow(c2, n - 1);
			}
		}
	}

	void SemiImplicitDiffusionAlgorithm::ComputeElements()
	{

	}

}