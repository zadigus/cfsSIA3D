#include "SemiImplicitDiffusionAlgorithm.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

#include "Numerics/LinSyst/LinSyst.hpp"
#include "Numerics/LinSyst/Vector.hpp"
#include "Numerics/LinSyst/Matrix.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "NumericsCoreParams.hpp"

#include <cassert>

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aDiffusionAlgo) 
		: FiniteDifferenceDiffusionAlgorithm(aDiffusionAlgo)
		, m_C1(aNumCoreParams->dt() / (2*m_Dx))
		, m_C2(m_C1/m_Dx)
	{
		
	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}
	
	void SemiImplicitDiffusionAlgorithm::Run()
	{
		// must build the LinSyst
		// must solve the LinSyst
		// must convert the Vector into a Grid
	}

	void SemiImplicitDiffusionAlgorithm::ComputeDiffusivity() 
	{
		double c1(0.), c2(0.);
		for (unsigned int i(1); i<m_Nx; ++i) 
		{
			for (unsigned int j(1); j<m_Ny; ++j) 
			{
				c1 = m_H->Staggered(i, j);
				c2 = StaggeredGradSurfNorm(i, j, m_H);
				D(i, j) = (Gamma()*c1 + rhogn()*Sl(i, j)) * pow(c1, n() + 1)*pow(c2, n() - 1);
			}
		}
	}

	void SemiImplicitDiffusionAlgorithm::BuildLinSyst()
	{ 
		ComputeDiffusivity();
		
		unsigned int idx(0), I(0); 
		double val(0.);
		std::unique_ptr<Vector> rhs(new Vector(m_Nx*m_Ny));
		std::unique_ptr<Matrix> A(new Matrix(m_Nx*m_Ny));
		
		for (int i(0); i < m_Nx; ++i) 
		{
			for (int j (0); j < m_Ny; ++j)
			{
				A->InsertNonZeroes(idx);
																						 val = D(i, j        ) * (-gradbx(i, j)     - gradby(i, j));
				if (j + 1 < m_Ny) 									val += D(i, j + 1    ) * (-gradbx(i, j)     + gradby(i, j + 1));
				if (i + 1 < m_Nx) 									val += D(i + 1, j    ) * (-gradby(i, j)     + gradbx(i + 1, j));
				if (i + 1 < m_Nx && j + 1 < m_Ny) 	val += D(i + 1, j + 1) * (+gradbx(i + 1, j) + gradby(i, j + 1));
				val *= m_C1; val += H(i, j);
				rhs->InsertValue(val);

				if (i - 1 >= 0) { // (i-1, j)
					assert(I - m_Ny >= 0); // distance from (i-1, j) to (i, j) is -Ny
					A->InsertColIdx(I - m_Ny);
					val = D(i, j); if (j + 1 < m_Ny) val += D(i, j + 1);
					val *= -m_C2;
					A->InsertValue(val);
					idx++;
				}

				if (j - 1 >= 0) { // (i, j-1)
					assert(I - 1 >= 0); // distance from (i, j-1) to (i, j) is -1
					A->InsertColIdx(I - 1);
					val = D(i, j); if (i + 1 < m_Nx) val += D(i + 1, j);
					val *= -m_C2;
					A->InsertValue(val);
					idx++;
				}

				A->InsertColIdx(I);
				val = D(i, j);
				if (i + 1 < m_Nx)              val += D(i + 1, j);
				if (j + 1 < m_Ny)              val += D(i, j + 1);
				if (i + 1 < m_Nx && j + 1 < m_Ny) val += D(i + 1, j + 1);
				val *= 2 * m_C2; val += 1;
				A->InsertValue(val);
				idx++;

				if (j + 1 < m_Ny) { // (i, j+1)
					assert(I + 1 >= 0); // distance from (i, j+1) to (i, j) is +1
					A->InsertColIdx(I + 1);
					val = D(i, j + 1); if (i + 1 < m_Nx) val += D(i + 1, j + 1);
					val *= -m_C2;
					A->InsertValue(val);
					idx++;
				}

				if (i + 1 < m_Nx) { // (i+1, j)
					assert(I + m_Ny >= 0); // distance from (i+1, j) to (i, j) is Ny
					A->InsertColIdx(I + m_Ny);
					val = D(i + 1, j); if (j + 1 < m_Ny) val += D(i + 1, j + 1);
					val *= -m_C2;
					A->InsertValue(val);
					idx++;
				}
				I++;
			}
		}
		A->InsertNonZeroes(idx); assert(I == m_LinSyst->MS()); assert(idx);

		m_LinSyst->SetMatrix(std::move(A)); // need to move, because unique_ptr can't be copied
		m_LinSyst->SetRHS(std::move(rhs));

	}

}