/*
 * SemiImplicitForwardSIA3D.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#ifndef SEMIIMPLICITFORWARDSIA3D_H_
#define SEMIIMPLICITFORWARDSIA3D_H_

#include "ForwardSIA3D.h"

class SemiImplicitForwardSIA3D: public ForwardSIA3D {
friend class SemiImplicitPrimalDualSIA3D;
public:
	SemiImplicitForwardSIA3D(int Nx, int Ny, double dx, double xll, double yll, double dt, double ti, double tf)
	: ForwardSIA3D(Nx, Ny, dx, xll, yll, dt, ti, tf) {  _C1 = _dt/(2*_dx); _C2 = _C1/_dx; }
	~SemiImplicitForwardSIA3D() { }

	// Construction of linear system
	void Diffusivity(int);
	void Diffusivity();
	void BuildDiffusion();
	void Diffusion();
	double Update();
};

#endif /* SEMIIMPLICITFORWARDSIA3D_H_ */
