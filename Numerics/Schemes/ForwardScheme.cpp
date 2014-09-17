/*
 * ForwardSIA3D.cpp
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#include "ForwardSIA3D.h"

//=========================================================================================
ForwardSIA3D::ForwardSIA3D(int Nx, int Ny, double dx, double xll, double yll, double dt, double ti, double tf): 
		_H1(NULL), _H2(NULL), _H3(NULL), _v(NULL), _B(NULL), _Sl(NULL), _Rh(NULL), 
		_ti(ti), _tf(tf), _Nx(Nx), _Ny(Ny), _dx(dx), _dt(dt), _size((int)((_tf-_ti)/_dt)+1), _store(false), _tol(0.0), _O(NULL) {
//=========================================================================================
	       _fs.initialize(_Nx, _Ny, _dx, xll, yll);
	  _gradfsx.initialize(_Nx, _Ny, _dx, xll, yll);
	  _gradfsy.initialize(_Nx, _Ny, _dx, xll, yll);
	        _D.initialize(_Nx, _Ny, _dx, xll, yll);
	        _H.initialize(_Nx, _Ny, _dx, xll, yll);
	       _HN.initialize(_Nx, _Ny, _dx, xll, yll);
	_ls = new LinSystSIA3D(_Nx*_Ny);

	frame(100, "Grid resolution");
	printInfo("XLL", xll);
	printInfo("YLL", yll); 
	printInfo("Nx", Nx);
	printInfo("Ny", Ny);
	printInfo("Space step", dx);

	frame(100, "Time resolution");
	printInfo("Initial time", ti);
	printInfo("Final time", tf);
	printInfo("Time step", dt);
}

//=========================================================================================
void ForwardSIA3D::GradFs() {
//=========================================================================================
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			_gradfsx(i, j) = (_fs(i, j) - _fs(i-1, j  ))/_dx; // gradient of the fixed surface
			_gradfsy(i, j) = (_fs(i, j) - _fs(i  , j-1))/_dx; // gradient of the fixed surface
		}
	}
}

//=========================================================================================
void ForwardSIA3D::SetData(Grid & b, Grid & s, Grid *H1, Grid *H2, Grid *H3, Grid *v, double *conv) {
//=========================================================================================
	assert(_store);
	assert(_Nx == b.get_nx()); assert(_Ny == b.get_ny()); assert(_dx == b.get_deltax()); assert(_dx == b.get_deltay());
	double tmp(0.); conv[0] = 0;
	for(int i=0; i<_Nx; i++) {
		for(int j=0; j<_Ny; j++) {
			tmp = fabs(_fs(i, j) - b(i, j));
			if(tmp > conv[0]) conv[0] = tmp;
			_fs(i, j) = b(i, j);
			_H(i, j)  = max(0., s(i, j) - _fs(i, j));
			for(int k=0; k<_size-1; k++) { // TODO: it would be better to let these pointers point to the other thicknesses instead of copying the values like this
				_H1[k](i, j) = H1[k](i, j);
				_H2[k](i, j) = H2[k](i, j);
				_H3[k](i, j) = H3[k](i, j);
				 _v[k](i, j) = v[k](i, j);
			}
			_H1[_size-1](i, j) = H1[_size-1](i, j);
			 _v[_size-1](i, j) = v[_size-1](i, j);
		}
	}
	GradFs();
}

//=========================================================================================
void ForwardSIA3D::SetBedrock(Grid & b, Grid & s) {
//=========================================================================================
	assert(_Nx == b.get_nx()); assert(_Ny == b.get_ny()); assert(_dx == b.get_deltax()); assert(_dx == b.get_deltay());
	assert(b.isCompatible(s));
	for(int i=0; i<_Nx; i++) {
		for(int j=0; j<_Ny; j++) {
			_fs(i, j) = b(i, j);
			_H(i, j)  = max(0., s(i, j) - _fs(i, j));
		}
	}
	GradFs();
}

//=========================================================================================
void ForwardSIA3D::SetParams(Vec X, Grid & s, bool DualBed, double *conv) {
// Sets model inputs (bedrock topography and model parameters) in the case of a primal-dual problem
// X: the new value of the bedrock topography and the model parameters is stored in the vector X, accessed with array x below
// s: initial surface topography, that is known
// DualBed: if true, then the bedrock topography is optimized, otherwise, it is not
// conv: array whose components are the norm of the difference between two successive iterates of the bedrock topography, the mass-balance, sliding, and rheology parameters
//=========================================================================================
	assert(conv != NULL);
	PetscReal *x; VecGetArray(X, &x);
	int idx(0), convNb(0); double tmp(0.); conv[convNb] = 0;
	if(DualBed) {
		for(int i=0; i<_Nx; i++) {
			for(int j=0; j<_Ny; j++) {
				tmp = fabs(_fs(i, j) - x[idx]);
				if(tmp > conv[convNb]) conv[convNb] = tmp;
				_fs(i, j) = x[idx];
				_H(i, j)  = max(0., s(i, j) - _fs(i, j));
				idx++;
			}
		}
		GradFs();
		convNb++;
	} else {
		for(int i=0; i<_Nx; i++)
			for(int j=0; j<_Ny; j++)
				_H(i, j)  = max(0., s(i, j) - _fs(i, j));
	}

	for(int i=0; i<_Rh->N(); i++) {
		if(_Rh->d(i)) {
			conv[convNb++] = fabs(_Rh->x(i)-x[idx]);
			_Rh->Set(i, x[idx++]);
		}
	}

	for(int i=0; i<_B->N(); i++) {
		if(_B->d(i)) {
			conv[convNb++] = fabs(_B->x(i)-x[idx]);
			_B->Set(i, x[idx++]);
		}
	}

	bool UpdtSl = false;
	for(int i=0; i<_Sl->N(); i++) {
		if(_Sl->d(i)) {
			conv[convNb++] = fabs(_Sl->x(i)-x[idx]);
			_Sl->Set(i, x[idx++]);
			UpdtSl = true;
		}
	}
	if(UpdtSl) _Sl->Generate(_fs, n());

	VecRestoreArray(X, &x);
}

//=========================================================================================
void ForwardSIA3D::Store() {
// Allows memory for ice thickness and velocity storage when it needs to be backed-up
//=========================================================================================
	assert(_H1 == NULL); assert(_H2 == NULL); assert(_H3 == NULL); assert(_v == NULL);
	_H1 = new Grid [_size]; _H2 = new Grid [_size-1]; _H3 = new Grid [_size-1]; _v = new Grid [_size];
	for(int i=0; i<_size-1; i++) {
		_H1[i].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
		_H2[i].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
		_H3[i].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
		 _v[i].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	}
	_H1[_size-1].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	 _v[_size-1].initialize(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	_store = true;
}

//=========================================================================================
void ForwardSIA3D::SetIterativeSolver() {
//=========================================================================================
	_ls->SetIterative();
}

//=========================================================================================
double ForwardSIA3D::StaggeredGradSurfNorm(int i, int j, Grid & H) {
// compute norm of gradient of grid in the staggered grid
// corresponds to alpha in the papers, which is |grad s|
//=========================================================================================
	assert(i-1>=0); assert(j-1>=0); assert(i<_Nx); assert(j<_Ny);
	return sqrt((_fs(i,   j) + H(i,   j) - _fs(i-1, j-1) - H(i-1, j-1))*(_fs(i,   j) + H(i,   j) - _fs(i-1, j-1) - H(i-1, j-1))
			    +(_fs(i, j-1) + H(i, j-1) - _fs(i-1,   j) - H(i-1,   j))*(_fs(i, j-1) + H(i, j-1) - _fs(i-1,   j) - H(i-1,   j)))/(sqrt(2)*_dx);
}

//=========================================================================================
void ForwardSIA3D::SurfaceVelocity(Grid & H, Grid & v) {
// Compute the norm of the horizontal velocity
//=========================================================================================
	// E is u_{i-1/2, j-1/2}
	Grid E(_Nx, _Ny, _dx, v.get_xll(), v.get_yll()); 
	double c1(0.), c2(0.);
	for(int i=1; i<_Nx; i++) {
		for(int j=1; j<_Ny; j++) {
			c1 = H.Staggered(i, j);
			c2 = StaggeredGradSurfNorm(i, j, H);
			E(i, j) = (Gamma()*c1*(n()+2)/(n()+1) + rhogn()*(*_Sl)(i, j))*pow(c1, n())*pow(c2, n()); // ((n+2)/(n+1) * Gamma * H + (rho*g/C)^n) * H^n * |grad s|^n; sl = (1/C)^n
		}
	}

	for(int i=1; i<_Nx-1; i++)
		for(int j=1; j<_Ny-1; j++)
			v(i, j) = 1./4. * (E(i, j)+E(i, j+1)+E(i+1, j)+E(i+1, j+1));
	E.Delete();
}

//==================================================================================================================
void ForwardSIA3D::Climate(int l) {
// Solves dH/dt = B with a Newton method
//==================================================================================================================
	_HN.Import(_H); // initialization of Newton process
	double errNewton(1), updt(0.), F(0), Fp(0); //, s(0);
	while(errNewton > 1e-6) {
		errNewton = 0;
		for(int i=0; i<_Nx; i++) {
			for(int j=0; j<_Ny; j++) {
				F = _HN(i, j) - _H(i, j) - _dt*(*_B)(_fs(i, j), _HN(i, j), _H(i, j));
				Fp= 1 - _dt*_B->ds(_fs(i, j), _HN(i, j), _H(i, j)); // derivative of mass balance wrt glacier surface
				updt = F/Fp; _HN(i, j) -= updt;
				if(fabs(updt) > errNewton) errNewton = fabs(updt);
			}
		}
	}
	_H.Import(_HN);
}

//==================================================================================================================
void ForwardSIA3D::Projection() {
// Ensures positivity of H
//==================================================================================================================
	for(int i=0; i<_Nx; i++)
		for(int j=0; j<_Ny; j++)
			_H(i, j) = Heaviside(_H(i, j)) * _H(i, j); // max(0., _H(i, j));
}

//==================================================================================================================
void ForwardSIA3D::Iterate(int l) {
// One full finite-difference time iteration
//==================================================================================================================
	Diffusion();
	if(_store) _H2[l].Import(_H);
	Climate(l); // from H2 = \tilde H^l, deduce H3 = \tilde\tilde H^l, which results from ablation/accumulation process only
	if(_store) _H3[l].Import(_H);
	Projection(); // from H3 = \tilde\tilde H^l, deduce H^{l+1} which results from the projection of the thickness onto a space of positive values
	if(_store) {
		_H1[l+1].Import(_H);
		SurfaceVelocity(_H, _v[l+1]);
	}
}

//==================================================================================================================
void ForwardSIA3D::Primal() {
// Solves the forward (primal) problem
//==================================================================================================================
	assert(_Sl != NULL); assert(_B != NULL); assert(_Rh != NULL);
	double t(_ti); int iter(1); Grid v(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
	if(_O != NULL) { // Surface and velocity outputs (to grid format)
		_O->Surface(_fs, _H, 0);
		SurfaceVelocity(_H, v);
		_O->Velocity(v, 0);
	}

	if(_store) { 
		_H1[0].Import(_H);
		SurfaceVelocity(_H, _v[0]);
	}

	// TODO: Careful: the sliding law must have been generated
	
	while(iter < _size) {
		Iterate(iter-1); // solving of the finite-difference scheme
		t += _dt;
		if(_O != NULL && !(iter%_O->Step())) { // Surface and velocity outputs (to grid format)
			_O->Surface(_fs, _H, iter); 
			SurfaceVelocity(_H, v);  
			_O->Velocity(v, iter);
		}
		iter++;
	}
	if(_O != NULL) { // Surface and velocity outputs (to grid format)
		_O->Surface(_fs, _H, iter-1); 
		SurfaceVelocity(_H, v);  
		_O->Velocity(v, iter-1);
	}
	v.Delete();
}

//==================================================================================================================
void ForwardSIA3D::Stationary() {
// Computes the stationary solution of the shallow ice equation
//==================================================================================================================
	assert(_Sl != NULL); assert(_B != NULL); assert(_Rh != NULL); assert(_tol>0.0);
	double t(_ti); int iter(1);
	if(_O != NULL) { // Surface output (to grid format)
		_O->Surface(_fs, _H, 0);
	}

	Grid tmp(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll()); double err(0.), errM(0.);
	while(true) {
		tmp.Import(_H);
		Iterate(iter-1); // finite-difference time iteration
		t += _dt;
		if(_O != NULL && !(iter%_O->Step())) {
			cout << addLeadingZeroes(iter, 10) << "\t" << errM << endl;
			_O->Surface(_fs, _H, iter); // Surface output (to grid format)
		}
		errM = 0;
		for(int i=0; i<_Nx; i++) { // computation of the maximal surface difference from one iteration to the next one
			for(int j=0; j<_Ny; j++) {
				err = fabs(tmp(i, j)-_H(i, j));
				if(err > errM)
					errM = err;
			}
		}
		if(errM < _tol) break; // stopping criterion
		iter++;
	}
	tmp.Delete();

	if(_O != NULL) {
		_O->Surface(_fs, _H, iter);
		Grid v(_Nx, _Ny, _dx, _H.get_xll(), _H.get_yll());
		SurfaceVelocity(_H, v);  
		_O->Velocity(v, iter); // Surface and velocity outputs (to grid format)
		v.Delete();
	}
}

//=========================================================================================
ForwardSIA3D::~ForwardSIA3D() {
//=========================================================================================
	if(_store) {
		for(int i=0; i<_size-1; i++) {
			_H1[i].Delete();
			_H2[i].Delete();
			_H3[i].Delete();
			 _v[i].Delete();
		}
		_H1[_size-1].Delete();
		 _v[_size-1].Delete();
		deleteArray(_H1); deleteArray(_H2); deleteArray(_H3); deleteArray(_v);
	}
	_store = false;
	_H.Delete(); _HN.Delete();
	_gradfsx.Delete(); _gradfsy.Delete(); 
	_D.Delete(); _fs.Delete();
	delete _B;
	delete _Sl;
	delete _Rh;
	delete _ls;
	if(_O != NULL) delete _O;
}
