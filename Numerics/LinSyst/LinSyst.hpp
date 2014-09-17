/*
 * LinSystSIA3D.h
 *
 *  Created on: Apr 9, 2013
 *      Author: lmichel
 */

#ifndef LINSYSTSIA3D_H_
#define LINSYSTSIA3D_H_

#include <iostream>
#include <vector>
#include "petsc.h"

using std::vector; using std::cerr; using std::endl;

// Linear system, used for all the schemes in the forward, inverse, dual problems

class LinSystSIA3D {
public:
	LinSystSIA3D(int MS) : _MS(MS) {
		VecCreateSeq(PETSC_COMM_SELF, _MS, &_X); // A and b must be created during each step
		KSPCreate(PETSC_COMM_SELF, &_solver);
		KSPSetType(_solver, KSPPREONLY);
		PC pc; KSPGetPC(_solver, &pc); PCSetType(pc, PCLU);
	}
	~LinSystSIA3D() {
		if(_b_values.size()) {
			VecDestroy(&_X);
//			KSPDestroy(&_solver); // TODO: why can't I destroy this here?
			_A_values.clear(); _b_values.clear();
		}
	}

	// Access to class members
	int 	MS() 					{ return _MS; }
	double	*Get      ()			{ double *x; VecGetArray(_X, &x); return x;}
	void 	Restore (double *x) 	{ VecRestoreArray(_X, &x); }

	// Filling linear system
	void Reset() { _r.clear(); _c.clear(); _A_values.clear(); _b_values.clear(); }
	void Insert_b(double val) 	{ _b_values.push_back(val); }
	void Insert_A(double val) 	{ _A_values.push_back(val); }
	void Insert_r(int val)		{ _r.push_back(val); }
	void Insert_c(int val)		{ _c.push_back(val); }

	// Solving linear system
	void SetIterative();
	void Solve();

protected:
	int _MS; // matrix size

	Vec _b, _X;
	Mat _A;
	KSP _solver;
	vector<int> _r, _c;
	vector<double> _A_values;
	vector<double> _b_values;
	//TODO: could be replaced with simple arrays of sizes
	// _r: Nx*Ny+1 = MS+1
	// _c: number of non-zeroes, i.e. D*(Nx*Ny-1)+1 = D*(Ms-1)+1, where D is 5 in the semi-implicit and 9 in the fully-implicit case
	// _M_values: same as _c, number of non-zeroes
	// _rhs_values: Nx*Ny = MS

	// Convergence params
	KSPConvergedReason _reason;
};

#endif /* LINSYSTSIA3D_H_ */
