#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Numerics/LinSyst/LinSyst.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo) 
		: FiniteDifferenceDiffusionAlgorithm(aDiffusionAlgo)
	{
		
	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
		// must build the LinSyst
		// must solve the LinSyst
		// must convert the vector<double> into a Grid
	}

	void SemiImplicitDiffusionAlgorithm::ComputeDiffusivity() 
	{
		double c1(0.), c2(0.);
		for (unsigned int i = 1; i<_Nx; ++i) 
		{
			for (unsigned int j = 1; j<_Ny; ++j) 
			{
				c1 = _H->Staggered(i, j);
				c2 = StaggeredGradSurfNorm(i, j, _H);
				D(i, j) = (Gamma()*c1 + rhogn()*Sl(i, j)) * pow(c1, n() + 1)*pow(c2, n() - 1);
			}
		}
	}

	void SemiImplicitDiffusionAlgorithm::BuildLinSyst()
	{ // TODO: define _C1, _C2, _gradfsx, _gradfsy
		ComputeDiffusivity();
		unsigned int idx(0), I(0); double val(0.);
		_LinSyst->Clear();
		for (int i(0); i < _Nx; ++i) 
		{
			for (int j (0); j < _Ny; ++j)
			{
				_LinSyst->InsertNonZeroes(idx);
																					 val = D(i, j        ) * (-_gradfsx(i, j)     - _gradfsy(i, j));
				if (j + 1 < _Ny) 									val += D(i, j + 1    ) * (-_gradfsx(i, j)     + _gradfsy(i, j + 1));
				if (i + 1 < _Nx) 									val += D(i + 1, j    ) * (-_gradfsy(i, j)     + _gradfsx(i + 1, j));
				if (i + 1 < _Nx && j + 1 < _Ny) 	val += D(i + 1, j + 1) * (+_gradfsx(i + 1, j) + _gradfsy(i, j + 1));
				val *= _C1; val += H(i, j);
				_LinSyst->InsertRHS(val);

				if (i - 1 >= 0) { // (i-1, j)
					assert(I - _Ny >= 0); // distance from (i-1, j) to (i, j) is -Ny
					_LinSyst->InsertColIdx(I - _Ny);
					val = D(i, j); if (j + 1 < _Ny) val += D(i, j + 1);
					val *= -_C2;
					_LinSyst->InsertMat(val);
					idx++;
				}

				if (j - 1 >= 0) { // (i, j-1)
					assert(I - 1 >= 0); // distance from (i, j-1) to (i, j) is -1
					_LinSyst->InsertColIdx(I - 1);
					val = D(i, j); if (i + 1 < _Nx) val += D(i + 1, j);
					val *= -_C2;
					_LinSyst->InsertMat(val);
					idx++;
				}

				_LinSyst->InsertColIdx(I);
				val = D(i, j);
				if (i + 1 < _Nx)              val += D(i + 1, j);
				if (j + 1 < _Ny)              val += D(i, j + 1);
				if (i + 1 < _Nx && j + 1 < _Ny) val += D(i + 1, j + 1);
				val *= 2 * _C2; val += 1;
				_LinSyst->InsertMat(val);
				idx++;

				if (j + 1 < _Ny) { // (i, j+1)
					assert(I + 1 >= 0); // distance from (i, j+1) to (i, j) is +1
					_LinSyst->InsertColIdx(I + 1);
					val = D(i, j + 1); if (i + 1 < _Nx) val += D(i + 1, j + 1);
					val *= -_C2;
					_LinSyst->InsertMat(val);
					idx++;
				}

				if (i + 1 < _Nx) { // (i+1, j)
					assert(I + _Ny >= 0); // distance from (i+1, j) to (i, j) is Ny
					_LinSyst->InsertColIdx(I + _Ny);
					val = D(i + 1, j); if (j + 1 < _Ny) val += D(i + 1, j + 1);
					val *= -_C2;
					_LinSyst->InsertMat(val);
					idx++;
				}
				I++;
			}
		}
		_LinSyst->InsertNonZeroes(idx); assert(I == _LinSyst->MS()); assert(idx);
	}

}