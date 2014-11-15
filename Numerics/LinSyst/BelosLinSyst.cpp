#include "BelosLinSyst.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include <iostream>

namespace N_Mathematics {

	BelosLinSyst::BelosLinSyst(N_Configuration::SubComponent* aLinSyst)
		: LinSyst(aLinSyst)
	{
		/*VecCreateSeq(PETSC_COMM_SELF, _MS, &_X); 
		KSPCreate(PETSC_COMM_SELF, &_solver);
		KSPSetType(_solver, KSPPREONLY);
		PC pc; 
		KSPGetPC(_solver, &pc); 
		PCSetType(pc, PCLU);*/
	}

	BelosLinSyst::~BelosLinSyst() {
		//if (_RHSValues.size()) {
			//VecDestroy(&_X);
			//			KSPDestroy(&_solver); // TODO: why can't I destroy this here?
		//}
	}

	/*void PETScLinSyst::SetIterative() { // TODO: that must come in the ctor
		KSPSetType(_solver, KSPGMRES);
		KSPGMRESSetRestart(_solver, 1500);
		KSPSetTolerances(_solver, 1e-5, PETSC_DEFAULT, 1e10, 1500);
		KSPGMRESSetOrthogonalization(_solver, KSPGMRESModifiedGramSchmidtOrthogonalization);
		PC pc; KSPGetPC(_solver, &pc); PCSetType(pc, PCILU);
	}*/

	void BelosLinSyst::Solve() {
		//MatCreateSeqAIJWithArrays(PETSC_COMM_SELF, _MS, _MS, &_NonZeroes[0], &_ColIdx[0], &_MatValues[0], &_A); // builds the matrix with CSR format and values
		//VecCreateSeqWithArray(PETSC_COMM_SELF, 1, _MS, &_RHSValues[0], &_b); // builds the vector 

		//// Solves the linear system
		//KSPSetOperators(_solver, _A, _A, SAME_NONZERO_PATTERN);
		//KSPSolve(_solver, _b, _X);
		//KSPGetConvergedReason(_solver, &_reason);
		//if (_reason <= 0) {
		//	std::cerr << "KSPSolve diverged with reason " << _reason << std::endl; // TODO: write that in a log file
		//	exit(1);
		//}
		//MatDestroy(&_A); VecDestroy(&_b);

		// TODO: fill m_X
	}

}
