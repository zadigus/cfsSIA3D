/*
 * FullyImplicitForwardSIA3D.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#ifndef FULLYIMPLICITFORWARDSIA3D_H_
#define FULLYIMPLICITFORWARDSIA3D_H_

#include "ForwardSIA3D.h"

class FullyImplicitForwardSIA3D : public ForwardSIA3D {
friend class FullyImplicitPrimalDualSIA3D;
public:
	FullyImplicitForwardSIA3D(int Nx, int Ny, double dx, double xll, double yll, double dt, double ti, double tf)
	: ForwardSIA3D(Nx, Ny, dx, xll, yll, dt, ti, tf) {
		_C1 = _dt/(4*_dx); _C2 = _C1/_dx;
		_C1m.initialize(_Nx, _Ny, _dx, xll, yll);
		_C1p.initialize(_Nx, _Ny, _dx, xll, yll);
		_C2m.initialize(_Nx, _Ny, _dx, xll, yll);
		_C2p.initialize(_Nx, _Ny, _dx, xll, yll);
	 	 _DD.initialize(_Nx, _Ny, _dx, xll, yll);
		_Gsx.initialize(_Nx, _Ny, _dx, xll, yll);
		_Gsy.initialize(_Nx, _Ny, _dx, xll, yll);
	}

	~FullyImplicitForwardSIA3D() {
		_C1m.Delete(); _C1p.Delete(); _C2m.Delete(); _C2p.Delete(); _DD.Delete(); _Gsx.Delete(); _Gsy.Delete();
	}

	// Construction of linear system
	void Diffusivity();
	void Diffusivity(int);
	void BuildDiffusion();
	void Diffusion();
	double Update();
};

#endif /* FULLYIMPLICITFORWARDSIA3D_H_ */
