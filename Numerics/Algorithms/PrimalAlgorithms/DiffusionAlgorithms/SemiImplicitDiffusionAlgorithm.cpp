#include "SemiImplicitDiffusionAlgorithm.hpp"

// Glacier
#include "Glacier/Glacier.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include "Glacier/GlacierComponents/Rheology/Rheology.hpp"
#include "Glacier/GlacierComponents/SlidingLaw/SlidingLaw.hpp"

// Linear system
#include "Numerics/LinSyst/LinSyst.hpp"
#include "Teuchos_RCP.hpp"
#include "Epetra_CrsMatrix.h"
#include "Epetra_Vector.h"

// Configuration
#include "Configuration/ModelConfiguration.hpp"
#include "Algorithms/NumericsCoreParams.hpp"

// Logger
#include "Utility/Logger/Logger.hpp"

namespace N_Mathematics {

	SemiImplicitDiffusionAlgorithm::SemiImplicitDiffusionAlgorithm(const NumericsCoreParams& aNumCoreParams, const N_Configuration::Component& aDiffusionAlgo)
		: FiniteDifferenceDiffusionAlgorithm(aDiffusionAlgo)
		, m_C1(aNumCoreParams.dt() / (2*m_Dx))
		, m_C2(m_C1/m_Dx)
	{
		// TODO: read further parameters here (see FullyImplicitClimateAlgorithm)

	}

	SemiImplicitDiffusionAlgorithm::~SemiImplicitDiffusionAlgorithm()
	{

	}

	void SemiImplicitDiffusionAlgorithm::setCrs()
	{
		LOG_INF("Setting matrix CRS structure");

		unsigned int idx(0), I(0), MS(m_Nx*m_Ny);
        std::vector<int> nnz, col;

		nnz.reserve(MS + 1);
		col.reserve(5 * MS); // penta-diagonal matrix

		for (int i(0); i < m_Nx; ++i)
		{
			for (int j(0); j < m_Ny; ++j) // must use ints here instead of unsigned ints because e.g. i-1 is checked
			{
				nnz.push_back(idx);

				if (i - 1 >= 0) { // (i-1, j)
					//assert(I - m_Ny >= 0); // distance from (i-1, j) to (i, j) is -Ny
					col.push_back(I - m_Ny);
					idx++;
				}

				if (j - 1 >= 0) { // (i, j-1)
					//assert(I - 1 >= 0); // distance from (i, j-1) to (i, j) is -1
					col.push_back(I - 1);
					idx++;
				}

				col.push_back(I); // (i, j)
				idx++;

				if (j + 1 < m_Ny) { // (i, j+1)
					//assert(I + 1 >= 0); // distance from (i, j+1) to (i, j) is +1
					col.push_back(I + 1);
					idx++;
				}

				if (i + 1 < m_Nx) { // (i+1, j)
					//assert(I + m_Ny >= 0); // distance from (i+1, j) to (i, j) is Ny
					col.push_back(I + m_Ny);
					idx++;
				}
				I++;
			}
		}
		nnz.push_back(idx); //assert(I == MS); assert(idx);

		m_LinSyst->setCrs(std::move(nnz), std::move(col));
	}

	void SemiImplicitDiffusionAlgorithm::computeDiffusivity() 
	{
		double c1(0.), c2(0.);
		for (unsigned int i(1); i<m_Nx; ++i) 
		{
			for (unsigned int j(1); j<m_Ny; ++j) 
			{
				c1 = m_H->Staggered(i, j);
				c2 = staggeredGradSurfNorm(i, j, m_H);
				D(i, j) = (Gamma()*c1 + rhogn()*Sl(i, j)) * pow(c1, n() + 1)*pow(c2, n() - 1);
			}
		}
	}

	void SemiImplicitDiffusionAlgorithm::fillLinSyst()
	{ // must be filled in accordance with Vector2Grid
		computeDiffusivity();
		
		unsigned int I(0);
		double val(0.);
		std::vector<int>    colIdx; 
		std::vector<double> values;
	
		colIdx.reserve(5);
		values.reserve(5);

        Teuchos::RCP<Epetra_Vector>    rhs(m_LinSyst->getRHS());
        Teuchos::RCP<Epetra_CrsMatrix> A  (m_LinSyst->getMatrix());

		for (int i(0); i < m_Nx; ++i) 
		{
			for (int j (0); j < m_Ny; ++j) // must use ints here instead of unsigned ints because e.g. i-1 is checked
			{
                                                                    val  = D(i, j        ) * (-gradbx(i, j)     - gradby(i, j));
				if (j + 1 < m_Ny) 									val += D(i, j + 1    ) * (-gradbx(i, j)     + gradby(i, j + 1));
				if (i + 1 < m_Nx) 									val += D(i + 1, j    ) * (-gradby(i, j)     + gradbx(i + 1, j));
				if (i + 1 < m_Nx && j + 1 < m_Ny) 	val += D(i + 1, j + 1) * (+gradbx(i + 1, j) + gradby(i, j + 1));
				val *= m_C1; val += H(i, j);
                (*rhs)[I] = val;

				if (i - 1 >= 0) { // (i-1, j)
					colIdx.push_back(I - m_Ny); // distance from (i-1, j) to (i, j) is -Ny
					val = D(i, j); if (j + 1 < m_Ny) val += D(i, j + 1);
					val *= -m_C2;
					values.push_back(val);
				}

				if (j - 1 >= 0) { // (i, j-1)
					colIdx.push_back(I - 1); // distance from (i, j-1) to (i, j) is -1
					val = D(i, j); if (i + 1 < m_Nx) val += D(i + 1, j);
					val *= -m_C2;
					values.push_back(val);
				}

				colIdx.push_back(I); // (i, j)
				val = D(i, j);
				if (i + 1 < m_Nx)              val += D(i + 1, j);
				if (j + 1 < m_Ny)              val += D(i, j + 1);
				if (i + 1 < m_Nx && j + 1 < m_Ny) val += D(i + 1, j + 1);
				val *= 2 * m_C2; val += 1;
				values.push_back(val);

				if (j + 1 < m_Ny) { // (i, j+1)
					colIdx.push_back(I + 1); // distance from (i, j+1) to (i, j) is +1
					val = D(i, j + 1); if (i + 1 < m_Nx) val += D(i + 1, j + 1);
					val *= -m_C2;
					values.push_back(val);
				}

				if (i + 1 < m_Nx) { // (i+1, j)
					colIdx.push_back(I + m_Ny); // distance from (i+1, j) to (i, j) is Ny
					val = D(i + 1, j); if (j + 1 < m_Ny) val += D(i + 1, j + 1);
					val *= -m_C2;
					values.push_back(val);
				}
				
//				A->setRow(I, values, colIdx);
                A->ReplaceGlobalValues(I, values.size(), &values[0], &colIdx[0]);

				I++;
				colIdx.clear();
				values.clear();
			}
		}

        std::ofstream ofs("Matrix.out", std::ios_base::app);
        A->Print(ofs);
        ofs.close();
	}

}
