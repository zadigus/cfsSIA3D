/*
 * FullyImplicitForwardSIA3D.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#include "FullyImplicitForwardSIA3D.h"

//==================================================================================================================
void FullyImplicitForwardSIA3D::Diffusivity() {
// Compute the diffusivity D and the various other quantities that arise in the linear systems, like F, G, and the coefficients C_1^\pm, C_2^\pm (see papers)
//==================================================================================================================
	Grid F(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll()), G(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	double c11(0.), c21(0.), c1(0.), c2(0.), tmp11(0.), tmp21(0.), tmp1(0.), tmp2(0.);
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			// Computation of D^{l-1}, F^l and G^l
			c11  = 	_H.Staggered(i, j); c21  = StaggeredGradSurfNorm(i, j,  _H);
			c1   = _HN.Staggered(i, j); c2   = StaggeredGradSurfNorm(i, j, _HN);
			tmp11 = pow(c11, n()); tmp21 = pow(c21, n()-1); tmp1 = pow(c1, n()); tmp2 = pow(c2, n()-1);
			F(i, j)  = ((n()+2)*Gamma()*c1+(n()+1)*rhogn()*(*_Sl)(i, j)) / 4. * tmp1  * tmp2; // H^{n+1}*alpha^{n-1}
			G(i, j)  = (n()-1.)/(2.*_dx*_dx) * (Gamma()*c1 + rhogn()*(*_Sl)(i, j)) * c1 * tmp1;   // H^{n+2}
			 _D(i, j)= (Gamma()*c11 + rhogn()*(*_Sl)(i, j)) * tmp11 * c11 * tmp21;
			_DD(i, j)= (Gamma()*c1  + rhogn()*(*_Sl)(i, j)) * tmp1  * c1  * tmp2;
			if(n() == 1) G(i, j) = 0;
			if(n() == 2) G(i, j) /= c2;
			// if n = 3, then alpha^{n-3} = 1

			_C1m(i, j) = F(i, j) - G(i, j)*(_fs(i, j-1)+_HN(i, j-1)-_fs(i-1,   j)-_HN(i-1,   j));
			_C1p(i, j) = F(i, j) + G(i, j)*(_fs(i, j-1)+_HN(i, j-1)-_fs(i-1,   j)-_HN(i-1,   j));
			_C2m(i, j) = F(i, j) - G(i, j)*(_fs(i,   j)+_HN(i,   j)-_fs(i-1, j-1)-_HN(i-1, j-1));
			_C2p(i, j) = F(i, j) + G(i, j)*(_fs(i,   j)+_HN(i,   j)-_fs(i-1, j-1)-_HN(i-1, j-1));

			_Gsx(i, j) = (_fs(i, j)+_HN(i, j)-_fs(i-1, j)-_HN(i-1, j))/_dx; // gradient of current surface in the Newton algorithm
			_Gsy(i, j) = (_fs(i, j)+_HN(i, j)-_fs(i, j-1)-_HN(i, j-1))/_dx;
		}
	}
	F.Delete(); G.Delete();
}

//==================================================================================================================
void FullyImplicitForwardSIA3D::Diffusivity(int l) {
// Same as previous routine, but in the case where the thicknesses are stored and an access to arrays H1, H2 is available
//==================================================================================================================
	Grid F(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll()), G(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	double c11(0.), c21(0.), c1(0.), c2(0.), tmp11(0.), tmp21(0.), tmp1(0.), tmp2(0.);
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			// Computation of D^{l-1}, F^l and G^l
			c11  = _H1[l].Staggered(i, j); c21  = StaggeredGradSurfNorm(i, j, _H1[l]);
			c1   = _H2[l].Staggered(i, j); c2   = StaggeredGradSurfNorm(i, j, _H2[l]);
			tmp11 = pow(c11, n()); tmp21 = pow(c21, n()-1); tmp1 = pow(c1, n()); tmp2 = pow(c2, n()-1);
			F(i, j)  = ((n()+2)*Gamma()*c1+(n()+1)*rhogn()*(*_Sl)(i, j)) / 4. * tmp1  * tmp2; // H^{n+1}*alpha^{n-1}
			G(i, j)  = (n()-1.)/(2.*_dx*_dx) * (Gamma()*c1 + rhogn()*(*_Sl)(i, j)) * c1 * tmp1;   // H^{n+2}
			_D(i, j)= (Gamma()*c11 + rhogn()*(*_Sl)(i, j)) * tmp11 * c11 * tmp21;
			_DD(i, j)= (Gamma()*c1  + rhogn()*(*_Sl)(i, j)) * tmp1  * c1  * tmp2;
			if(n() == 1) G(i, j) = 0;
			if(n() == 2) G(i, j) /= c2;
			// if n = 3, then alpha^{n-3} = 1

			_C1m(i, j) = F(i, j) - G(i, j)*(_fs(i, j-1)+_H2[l](i, j-1)-_fs(i-1,   j)-_H2[l](i-1,   j));
			_C1p(i, j) = F(i, j) + G(i, j)*(_fs(i, j-1)+_H2[l](i, j-1)-_fs(i-1,   j)-_H2[l](i-1,   j));
			_C2m(i, j) = F(i, j) - G(i, j)*(_fs(i,   j)+_H2[l](i,   j)-_fs(i-1, j-1)-_H2[l](i-1, j-1));
			_C2p(i, j) = F(i, j) + G(i, j)*(_fs(i,   j)+_H2[l](i,   j)-_fs(i-1, j-1)-_H2[l](i-1, j-1));

			_Gsx(i, j) = (_fs(i, j)+_H2[l](i, j)-_fs(i-1, j)-_H2[l](i-1, j))/_dx;
			_Gsy(i, j) = (_fs(i, j)+_H2[l](i, j)-_fs(i, j-1)-_H2[l](i, j-1))/_dx;
		}
	}
	F.Delete(); G.Delete();
}

//=========================================================================================
void FullyImplicitForwardSIA3D::BuildDiffusion() {
// Builds the linear system to be solved at each Newton iteration; the matrix is nonadiagonal
// This routine is called each time a Newton iteration is performed
// All matrix and vector elements are stored in members _A_values and _b_values; the routine also defines the CSR structure of the matrix (Insert_r, Insert_c)
// See LinSystSIA3D.h for more details about the linear system
//=========================================================================================
	int idx(0), I(0); double val(0.);
	_ls->Reset();

	Diffusivity();

	for(int i=0; i<_Nx; i++) {
		for(int j=0; j<_Ny; j++) {
			_ls->Insert_r(idx);

			if(i > 0 && j > 0) {
											val  =  _HN(i, j)-_H(i, j) 
												   +_C1*_D(i,    j)*(GradSx(i,   j) + GradSy(i,  j))+_C1*_DD(i,    j)*(_Gsx(i,  j)+_Gsy(i,   j));
				if(i+1 < _Nx) 			   	val += -_C1*_D(i+1,  j)*(GradSx(i+1, j) - GradSy(i,  j))-_C1*_DD(i+1,  j)*(_Gsx(i+1,j)-_Gsy(i,   j));
				if(j+1 < _Ny) 			   	val += -_C1*_D(i,  j+1)*(GradSy(i, j+1) - GradSx(i,  j))+_C1*_DD(i,  j+1)*(_Gsx(i,  j)-_Gsy(i, j+1));
				if(i+1 < _Nx && j+1 < _Ny) 	val += -_C1*_D(i+1,j+1)*(GradSx(i+1, j) + GradSy(i,j+1))-_C1*_DD(i+1,j+1)*(_Gsx(i+1,j)+_Gsy(i, j+1));
			} else
				val = 0;
			_ls->Insert_b(val);

			if(i-1 >= 0 && j-1 >= 0) { // (i-1, j-1)
				assert(I-_Ny-1>=0); // distance from (i-1, j-1) to (i, j) is -(Ny+1)
				_ls->Insert_c(I-_Ny-1);
				val = _C1*_C2m(i, j)*(_Gsx(i, j)+_Gsy(i, j));
				_ls->Insert_A(val);
				idx++;
			}

			if(i-1 >= 0) { // (i-1, j)
				assert(I-_Ny>=0); // distance from (i-1, j) to (i, j) is -Ny
				_ls->Insert_c(I-_Ny);
				val =  _C1*_C1m(i, j)*(_Gsx(i, j)+_Gsy(i, j))-_C2*_DD(i, j);
				if(j+1 < _Ny) val += -_C1*_C2m(i, j+1)*(_Gsy(i, j+1)-_Gsx(i, j))-_C2*_DD(i, j+1);
				_ls->Insert_A(val);
				idx++;
			}

			if(i-1 >= 0 && j+1 < _Ny) { // (i-1, j+1)
				assert(I-_Ny+1>=0); // distance from (i-1, j+1) to (i, j) is -(Ny-1)
				_ls->Insert_c(I-_Ny+1);
				val = -_C1*_C1m(i, j+1)*(_Gsy(i, j+1)-_Gsx(i, j));
				_ls->Insert_A(val);
				idx++;
			}

			if(j-1 >= 0) { // (i, j-1)
				assert(I-1>=0); // distance from (i, j-1) to (i, j) is -1
				_ls->Insert_c(I-1);
				val =  _C1*_C1p(i, j)*(_Gsx(i, j)+_Gsy(i, j))-_C2*_DD(i, j);
				if(i+1 < _Nx) val += -_C1*_C2m(i+1, j)*(_Gsx(i+1, j)-_Gsy(i, j))-_C2*_DD(i+1, j);
				_ls->Insert_A(val);
				idx++;
			}

			_ls->Insert_c(I);
									   val  = 1 - _C1 * (-_C2p(i,     j)*_Gsx(i,   j) -_C2p(i,     j)*_Gsy(i,   j)) + 2*_C2 * _DD(i,     j);
			if(i+1 < _Nx)              val +=   - _C1 * ( _C1m(i+1,   j)*_Gsx(i+1, j) -_C1m(i+1,   j)*_Gsy(i,   j)) + 2*_C2 * _DD(i+1,   j);
			if(j+1 < _Ny)              val +=   - _C1 * (-_C1p(i,   j+1)*_Gsx(i,   j) +_C1p(i,   j+1)*_Gsy(i, j+1)) + 2*_C2 * _DD(i,   j+1);
			if(i+1 < _Nx && j+1 < _Ny) val +=   - _C1 * ( _C2m(i+1, j+1)*_Gsx(i+1, j) +_C2m(i+1, j+1)*_Gsy(i, j+1)) + 2*_C2 * _DD(i+1, j+1);
			_ls->Insert_A(val);
			idx++;

			if(j+1 < _Ny) { // (i, j+1)
				assert(I+1>=0); // distance from (i, j+1) to (i, j) is +1
				_ls->Insert_c(I+1);
				val = -_C1*_C2p(i, j+1)*(_Gsy(i, j+1)-_Gsx(i, j))-_C2*_DD(i, j+1);
				if(i+1 < _Nx) val += -_C1*_C1m(i+1, j+1)*(_Gsx(i+1, j)+_Gsy(i, j+1))-_C2*_DD(i+1, j+1);
				_ls->Insert_A(val);
				idx++;
			}


			if(i+1 < _Nx && j-1 >= 0) { // (i+1, j-1)
				assert(I+_Ny-1>=0); // distance from (i+1, j-1) to (i, j) is Ny-1
				_ls->Insert_c(I+_Ny-1);
				val = -_C1*_C1p(i+1, j)*(_Gsx(i+1, j)-_Gsy(i, j));
				_ls->Insert_A(val);
				idx++;
			}

			if(i+1 < _Nx) { // (i+1, j)
				assert(I+_Ny>=0); // distance from (i+1, j) to (i, j) is Ny
				_ls->Insert_c(I+_Ny);
				val = -_C1*_C2p(i+1, j)*(_Gsx(i+1, j)-_Gsy(i, j))-_C2*_DD(i+1, j);
				if(j+1 < _Ny) val += -_C1*_C1p(i+1, j+1)*(_Gsx(i+1, j)+_Gsy(i, j+1))-_C2*_DD(i+1, j+1);
				_ls->Insert_A(val);
				idx++;
			}

			if(i+1 < _Nx && j+1 < _Ny) { // (i+1, j+1)
				assert(I+_Ny+1>=0); // distance from (i+1, j+1) to (i, j) is Ny+1
				_ls->Insert_c(I+_Ny+1);
				val = -_C1*_C2p(i+1, j+1)*(_Gsx(i+1, j)+_Gsy(i, j+1));
				_ls->Insert_A(val);
				idx++;
			}
			I++;
		}
	}
	_ls->Insert_r(idx); assert(I==_ls->MS()); assert(idx);
}

//=========================================================================================
double FullyImplicitForwardSIA3D::Update() {
// Newton update of the ice thickness
//=========================================================================================
	double *x = _ls->Get();
	int I(0);
	double err(0.), updt(0.), maxErr(0.);
	for(int i=0; i<_Nx; i++) {
		for(int j=0; j<_Ny; j++) { // we solved DF(H^k)x = F(H^k), with x = H^k - H^{k+1}
			updt = _HN(i, j) - x[I++]; // H^{k+1} = H^k - x
			// computation of the discrepancy with the previous solution
			err = fabs(updt-_HN(i, j)); // indices in the linear system are shifted by 1
			if(err > maxErr) maxErr = err;
			// if max x-H < epsilon ; then break out of the while loop
			_HN(i, j) = updt; // update the current thickness
			if(std::isnan(updt)) {
				cerr << "Not-a-number encountered at position: " << _HN.X(i) << ", " << _HN.Y(j) << endl;
				exit(1);
			}
		}
	}
	_ls->Restore(x);
	return maxErr;
}

//=========================================================================================
void FullyImplicitForwardSIA3D::Diffusion() {
// Newton method that solves for the diffusion equation
//=========================================================================================
	_HN.Import(_H);// initialize Newton process
	int maxNewtonIter(1e3), nbNewtonIter(0); double newtonTol(1e-6), err(0.);
	while(nbNewtonIter < maxNewtonIter) {
		BuildDiffusion();    // build A, b
		_ls->Solve();        // solve A*X = b
		err = Update();      // set H2 as a function of X
		if(err < newtonTol) break;
		nbNewtonIter++;
	}
	_H.Import(_HN);
}
