#include "PETScLinSyst.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	PETScLinSyst::PETScLinSyst(N_Configuration::SubComponent* aLinSyst, int aMS)
		: LinSyst(aLinSyst, aMS)
	{
		/*VecCreateSeq(PETSC_COMM_SELF, m_MS, &m_X); 
		KSPCreate(PETSC_COMM_SELF, &m_Solver);
		KSPSetType(m_Solver, KSPPREONLY);
		PC pc; 
		KSPGetPC(m_Solver, &pc); 
		PCSetType(pc, PCLU);*/
	}

	PETScLinSyst::~PETScLinSyst() {
		//if (_RHSValues.size()) {
			//VecDestroy(&m_X);
			//			KSPDestroy(&m_Solver); // TODO: why can't I destroy this here?
		//}
	}

	/*void PETScLinSyst::SetIterative() { // TODO: that must come in the ctor
		KSPSetType(m_Solver, KSPGMRES);
		KSPGMRESSetRestart(m_Solver, 1500);
		KSPSetTolerances(m_Solver, 1e-5, PETSC_DEFAULT, 1e10, 1500);
		KSPGMRESSetOrthogonalization(m_Solver, KSPGMRESModifiedGramSchmidtOrthogonalization);
		PC pc; KSPGetPC(m_Solver, &pc); PCSetType(pc, PCILU);
	}*/

	void PETScLinSyst::Solve() {
		//MatCreateSeqAIJWithArrays(PETSC_COMM_SELF, m_MS, m_MS, &m_NonZeroes[0], &m_ColIdx[0], &m_MatValues[0], &m_A); // builds the matrix with CSR format and values
		//VecCreateSeqWithArray(PETSC_COMM_SELF, 1, m_MS, &m_RHSValues[0], &m_b); // builds the vector 

		//// Solves the linear system
		//KSPSetOperators(m_Solver, m_A, m_A, SAME_NONZERO_PATTERN);
		//KSPSolve(m_Solver, m_b, m_X);
		//KSPGetConvergedReason(m_Solver, &m_Reason);
		//if (m_Reason <= 0) {
		//	std::cerr << "KSPSolve diverged with reason " << m_Reason << std::endl; // TODO: write that in a log file
		//	exit(1);
		//}
		//MatDestroy(&m_A); VecDestroy(&m_b);

		// TODO: return a vector of doubles please
		//return Vector(MS());
	}

}
