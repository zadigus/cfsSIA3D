/*
 * SemiImplicitForwardSIA3D.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#include "SemiImplicitForwardSIA3D.h"

//==================================================================================================================
void SemiImplicitForwardSIA3D::Diffusivity() {
// See FullyImplicitForwardSIA3D for more comments; this is exactly the same, but simpler, because this implements the semi-implicit finite-difference scheme
//==================================================================================================================
	double c1(0.), c2(0.);
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			c1 = _H.Staggered(i, j);
			c2 = StaggeredGradSurfNorm(i, j, _H);
			_D(i, j) = (Gamma()*c1 + rhogn()*(*_Sl)(i, j)) * pow(c1, n()+1)*pow(c2, n()-1);
		}
	}
}

//==================================================================================================================
void SemiImplicitForwardSIA3D::Diffusivity(int l) {
//==================================================================================================================
	double c1(0.), c2(0.);
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			c1 = _H1[l].Staggered(i, j);
			c2 = StaggeredGradSurfNorm(i, j, _H1[l]);
			_D(i, j) = (Gamma()*c1 + rhogn()*(*_Sl)(i, j)) * pow(c1, n()+1)*pow(c2, n()-1);
		}
	}
}

//=========================================================================================
void SemiImplicitForwardSIA3D::BuildDiffusion() {
// The matrix is pentadiagonal only
//=========================================================================================
	Diffusivity();
	int idx(0), I(0); double val(0.);
	_ls->Reset();
	for(int i=0; i<_Nx; i++) {
		for(int j=0; j<_Ny; j++) {
			_ls->Insert_r(idx);
										val  = _D(i,     j) * (-_gradfsx(i, j)   - _gradfsy(i, j));
			if(j+1 < _Ny) 				val += _D(i,   j+1) * (-_gradfsx(i, j)   + _gradfsy(i, j+1));
			if(i+1 < _Nx) 				val += _D(i+1,   j) * (-_gradfsy(i, j)   + _gradfsx(i+1, j));
			if(i+1 < _Nx && j+1 < _Ny) 	val += _D(i+1, j+1) * (+_gradfsx(i+1, j) + _gradfsy(i, j+1));
			val *= _C1; val += _H(i, j);
			_ls->Insert_b(val);

			if(i-1 >= 0) { // (i-1, j)
				assert(I-_Ny>=0); // distance from (i-1, j) to (i, j) is -Ny
				_ls->Insert_c(I-_Ny);
				val = _D(i, j); if(j+1 < _Ny) val += _D(i, j+1);
				val *= -_C2;
				_ls->Insert_A(val);
				idx++;
			}

			if(j-1 >= 0) { // (i, j-1)
				assert(I-1>=0); // distance from (i, j-1) to (i, j) is -1
				_ls->Insert_c(I-1);
				val = _D(i, j); if(i+1 < _Nx) val += _D(i+1, j);
				val *= -_C2;
				_ls->Insert_A(val);
				idx++;
			}

			_ls->Insert_c(I);
			val  = _D(i,     j);
			if(i+1 < _Nx)              val += _D(i+1,   j);
			if(j+1 < _Ny)              val += _D(i,   j+1);
			if(i+1 < _Nx && j+1 < _Ny) val += _D(i+1, j+1);
			val *= 2*_C2; val += 1;
			_ls->Insert_A(val);
			idx++;

			if(j+1 < _Ny) { // (i, j+1)
				assert(I+1>=0); // distance from (i, j+1) to (i, j) is +1
				_ls->Insert_c(I+1);
				val = _D(i, j+1); if(i+1 < _Nx) val += _D(i+1, j+1);
				val *= -_C2;
				_ls->Insert_A(val);
				idx++;
			}

			if(i+1 < _Nx) { // (i+1, j)
				assert(I+_Ny>=0); // distance from (i+1, j) to (i, j) is Ny
				_ls->Insert_c(I+_Ny);
				val = _D(i+1, j); if(j+1 < _Ny) val += _D(i+1, j+1);
				val *= -_C2;
				_ls->Insert_A(val);
				idx++;
			}
			I++;
		}
	}
	_ls->Insert_r(idx); assert(I==_ls->MS()); assert(idx);
}

//=========================================================================================
double SemiImplicitForwardSIA3D::Update() {
//=========================================================================================
	double *x = _ls->Get();
	int I(0);
	for(int i=0; i<_Nx; i++)
		for(int j=0; j<_Ny; j++)
			_H(i, j) = x[I++];
	_ls->Restore(x);
	return 0;
}

//=========================================================================================
void SemiImplicitForwardSIA3D::Diffusion() {
//=========================================================================================
	BuildDiffusion();	// build A, b
	_ls->Solve();	    // solve A*X = b
	Update();	        // set H2 as a function of X
}
