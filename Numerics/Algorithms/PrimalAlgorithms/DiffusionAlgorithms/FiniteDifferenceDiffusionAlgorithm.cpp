#include "FiniteDifferenceDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Numerics/LinSyst/LinSystFactory.hpp"
#include "Numerics/LinSyst/LinSyst.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	FiniteDifferenceDiffusionAlgorithm::FiniteDifferenceDiffusionAlgorithm(N_Configuration::Component* aDiffusionAlgo) 
		: FiniteDifferencePrimalAlgorithm(aDiffusionAlgo)
		, _Rh(N_Glacier::Glacier::getInstance()->Rh())
		, _Sl(N_Glacier::Glacier::getInstance()->Sl())
		, _D(new Grid(_Nx, _Ny, _Dx, _H->Dy()))
		//, _LinSyst(new LinSyst(_Nx*_Ny)) // TODO: give the Component's parameters too? 
		, _LinSyst(nullptr)
	{
		//assert(_Dx == _H->Dy()); // TODO: enforce that somewhere else
		_LinSyst.reset(LinSystFactory::make(_Nx*_Ny, aDiffusionAlgo)); // TODO: give it sub-component LinSyst of component Diffusion
	}

	FiniteDifferenceDiffusionAlgorithm::~FiniteDifferenceDiffusionAlgorithm()
	{

	}
	
	double FiniteDifferenceDiffusionAlgorithm::StaggeredGradSurfNorm(unsigned int i, unsigned int j, const std::shared_ptr<Grid>& H) {
		// because this function is also used in the FullyImplicit version
		assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < _Nx); assert(j < _Ny);
		return sqrt((b(i, j    ) + (*H)(i, j    ) - b(i - 1, j - 1) - (*H)(i - 1, j - 1))*(b(i, j    ) + (*H)(i, j    ) - b(i - 1, j - 1) - (*H)(i - 1, j - 1))
							+ (b(i, j - 1) + (*H)(i, j - 1) - b(i - 1, j    ) - (*H)(i - 1, j    ))*(b(i, j - 1) + (*H)(i, j - 1) - b(i - 1, j    ) - (*H)(i - 1, j    ))) / (sqrt(2)*_Dx);
	}

	double& FiniteDifferenceDiffusionAlgorithm::D(unsigned int i, unsigned int j)
	{
		return (*_D)(i, j);
	}

	double FiniteDifferenceDiffusionAlgorithm::Gamma()
	{
		return _Rh->Gamma();
	}

	double FiniteDifferenceDiffusionAlgorithm::rhogn()
	{
		return _Rh->rhogn();
	}

	double FiniteDifferenceDiffusionAlgorithm::n()
	{
		return _Rh->n();
	}

	double  FiniteDifferenceDiffusionAlgorithm::Sl(unsigned int i, unsigned int j)
	{
		return (*_Sl)(i, j);
	}

}