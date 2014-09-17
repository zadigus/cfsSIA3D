/*
 * LinSystSIA3D.cpp
 *
 *  Created on: Apr 9, 2013
 *      Author: lmichel
 */

#include "LinSystSIA3D.h"

//=========================================================================================
void LinSystSIA3D::SetIterative() {
//=========================================================================================
	KSPSetType(_solver, KSPGMRES);
	KSPGMRESSetRestart(_solver, 1500);
	KSPSetTolerances(_solver, 1e-5, PETSC_DEFAULT, 1e10, 1500);
	KSPGMRESSetOrthogonalization(_solver, KSPGMRESModifiedGramSchmidtOrthogonalization);
	PC pc; KSPGetPC(_solver, &pc); PCSetType(pc, PCILU);
}

//==================================================================================================================
void LinSystSIA3D::Solve() {
//==================================================================================================================
	MatCreateSeqAIJWithArrays(PETSC_COMM_SELF, _MS, _MS, &_r[0], &_c[0], &_A_values[0], &_A); // builds the matrix with CSR format and values
	VecCreateSeqWithArray    (PETSC_COMM_SELF, 1, _MS, &_b_values[0], &_b); // builds the vector 

	// Solves the linear system
	KSPSetOperators(_solver, _A, _A, SAME_NONZERO_PATTERN);
	KSPSolve(_solver, _b, _X);
	KSPGetConvergedReason(_solver, &_reason);
	if(_reason <= 0) {
		cerr << "KSPSolve diverged with reason " << _reason << endl;
		exit(1);
	}
	MatDestroy(&_A); VecDestroy(&_b);
}
