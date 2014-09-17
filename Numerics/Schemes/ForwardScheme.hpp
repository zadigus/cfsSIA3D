/*
 * ForwardSIA3D.h
 *
 *  Created on: Apr 4, 2013
 *      Author: lmichel
 */

#ifndef FORWARDSIA3D_H_
#define FORWARDSIA3D_H_

#include <cassert>
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <ctime>
#include <vector>

#include "maths.h"
#include "Grid.h"
#include "param.h"

#include "MassBalance.h"
#include "SlidingLaw.h"
#include "Rheology.h"
#include "Measurements.h"
#include "LinSystSIA3D.h"
#include "OutputSIA3D.h"

// interface class for shallow ice approximation; base class for every computation
class ForwardSIA3D {
friend class PrimalDualSIA3D;
friend class OutputSIA3D;
friend class DataFactory;
public:
	ForwardSIA3D(int, int, double, double, double, double, double, double);
	virtual ~ForwardSIA3D();

	// Primal problem
	void Projection();         // compute projection step
	void Iterate(int);         // compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
	void Primal(); 	           // compute one whole evolution from time ti to time tf
	void Stationary();         // compute the geometry's stationary state
	void Store(); 						 // if a dual problem is considered, then every velocity and ice thickness must be stored

	// Interfaced routines for the primal problem, that solve for the diffusion and mass-balance steps
	virtual void Climate(int); 	                  // compute step dh/dt = B
	virtual void Diffusivity()   	       = 0;
	virtual void Diffusivity(int)	       = 0;   // if called with an int, then Diffusivity calls _H1, _H2, etc.
	virtual void Diffusion()      	     = 0;
	virtual void BuildDiffusion()     	 = 0;
	virtual double Update()       	     = 0;
	virtual void Init(Grid &, Grid &, Measurements *, double) { } // used for the quasi-stationary inverse method, because the definition of _fs is different in this case

	// Getters
	SlidingLaw *Sl() { return _Sl; }
	MassBalance *B() { return _B; }
	Rheology *Rh() { return _Rh; }
	double ti() { return _ti; }
	double tf() { return _tf; }
	int TimeSize() { return _size; }
	double StaggeredGradSurfNorm(int, int, Grid &);
	double StaggeredGradFSNorm(int, int);
	void SurfaceVelocity(Grid &, Grid &);
	double GradS1x(int i, int j, int l) { assert(_H1 != NULL); assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return _gradfsx(i, j) + (_H1[l](i, j)-_H1[l](i-1, j))/_dx; }
	double GradS1y(int i, int j, int l) { assert(_H1 != NULL); assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return _gradfsy(i, j) + (_H1[l](i, j)-_H1[l](i, j-1))/_dx; }
	double GradS2x(int i, int j, int l) { assert(_H2 != NULL); assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return _gradfsx(i, j) + (_H2[l](i, j)-_H2[l](i-1, j))/_dx; }
	double GradS2y(int i, int j, int l) { assert(_H2 != NULL); assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return _gradfsy(i, j) + (_H2[l](i, j)-_H2[l](i, j-1))/_dx; }
	double GradSx(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return _gradfsx(i, j) + (_H(i, j)-_H(i-1, j))/_dx; }
	double GradSy(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return _gradfsy(i, j) + (_H(i, j)-_H(i, j-1))/_dx; }
	double GradFSx(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return _gradfsx(i, j); }
	double GradFSy(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return _gradfsy(i, j); }
	double GradHx(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return (_H(i, j)-_H(i-1, j))/_dx; }
	double GradHy(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return (_H(i, j)-_H(i, j-1))/_dx; }
	double GradHNx(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!i) return 0; else return (_HN(i, j)-_HN(i-1, j))/_dx; }
	double GradHNy(int i, int j) { assert(0 <= i && i < _Nx); assert(0 <= j && j < _Ny); if(!j) return 0; else return (_HN(i, j)-_HN(i, j-1))/_dx; }
	LinSystSIA3D *ls() { return _ls; }
	double dt() { return _dt; }
	double dx() { return _dx; }
	int Nx() { return _Nx; }
	int Ny() { return _Ny; }
	int n() { return _Rh->n(); }
	double rhogn() { return _Rh->rhogn(); }
	double Gamma() { return _Rh->Gamma(); }
	double A() { return _Rh->A(); }
	double fs(int i, int j) { return _fs(i, j); }
	double Sl(int i, int j) { return (*_Sl)(i, j); }
	double H1(int l, int i, int j) { assert(_H1 != NULL); return _H1[l](i, j); }
	double H2(int l, int i, int j) { assert(_H2 != NULL); return _H2[l](i, j); }
	double H3(int l, int i, int j) { assert(_H3 != NULL); return _H3[l](i, j); }
	double S(int l, int i, int j) { assert(_H1 != NULL); return _fs(i, j) + _H1[l](i, j); }
	double S(int i, int j) { return _fs(i, j) + _H(i, j); }
	double H(int i, int j) { return _H(i, j); }

	double StaggeredH1(int i, int j, int l) { assert(_H1 != NULL); return _H1[l].Staggered(i, j); }
	double StaggeredH2(int i, int j, int l) { assert(_H2 != NULL); return _H2[l].Staggered(i, j); }
	double StaggeredGradNormS1(int i, int j, int l) { assert(_H1 != NULL); return StaggeredGradSurfNorm(i, j, _H1[l]); }
	double StaggeredGradNormS2(int i, int j, int l) { assert(_H2 != NULL); return StaggeredGradSurfNorm(i, j, _H2[l]); }

	void   D(int i, int j, double val) {  _D(i, j) = val; }
	void  DD(int i, int j, double val) { _DD(i, j) = val; }

	double   D(int i, int j) { return   _D(i, j); }
	double  DD(int i, int j) { return  _DD(i, j); }
	double C1m(int i, int j) { return _C1m(i, j); }
	double C2m(int i, int j) { return _C2m(i, j); }
	double C1p(int i, int j) { return _C1p(i, j); }
	double C2p(int i, int j) { return _C2p(i, j); }
	double Gsx(int i, int j) { return _Gsx(i, j); }
	double Gsy(int i, int j) { return _Gsy(i, j); }

	double C1() { return _C1; }
	double C2() { return _C2; }

	// Setters
	void SetData(Grid &, Grid &, Grid *, Grid *, Grid *, Grid *, double *);
	void GradFs();
	void SetBedrock(Grid &, Grid &);
	void SetSlidingLaw (SlidingLaw *sl)  { _Sl = sl; }
	void SetMassBalance(MassBalance *mb) {  _B = mb; }
	void SetRheology(Rheology *rh) {  _Rh = rh; }
	void SetParams(Vec, Grid &, bool, double *);
	void SetParams(Vec, Grid &, bool, Grid *, Grid *, Grid *, Grid *, double *);
	void SetOutput(OutputSIA3D *O) { _O = O; }

	// Data Export
	void 	ExportSlidingLaw(string fileName) { _Sl->Export(fileName); }
	void 	ExportBedrock(string fileName) 	{ _fs.Export(fileName); }
	void 	ExportSurface(string fileName)	    { Grid s = _fs+_H; s.Export(fileName); s.Delete(); }
	void	ExportSurface(string fileName, int l) { assert(_store); Grid s = _fs+_H1[l]; s.Export(fileName); s.Delete(); }
	void	ExportMassBalance(string fileName) { assert(_store); _B->Export(_fs, _H, fileName); }
	void	ExportVelocity(string fileName) { assert(_store); _v[_size-1].Export(fileName); }
	void 	ExportH1(string fileName, int l) { assert(_store); _H1[l].Export(fileName); }
	void 	ExportH2(string fileName, int l) { assert(_store); _H2[l].Export(fileName); }
	void 	ExportH3(string fileName, int l) { assert(_store); _H3[l].Export(fileName); }

	// Linear system
	void SetIterativeSolver();
	void Solve();

protected:
	// Glacier geometry
	Grid    	   _fs;   // fixed surface (bedrock in the PrimalSIA3D and PrimalDualSIA3D cases; surface in the InverseSIA3D case)
	Grid  	_gradfsx; // d(_fs)/dx
	Grid  	_gradfsy; // d(_fs)/dy
	Grid       	  _D; // staggered diffusivity
	Grid      	*_H1; // H (stored)
	Grid      	*_H2; // \tilde H (stored)
	Grid      	*_H3; // \tilde\tilde H (stored)
	Grid       	 *_v; // velocity (stored)
	Grid          _H; // thickness
	Grid         _HN; // thickness for Newton method

	// Physics
	MassBalance  *_B; // surface mass-balance (contains whatever useful coefficients for B there can be; e.g. am, ac, ELA, m1, m2, etc.)
	SlidingLaw  *_Sl; // sliding coefficients (contains Zsl, Csl, Cn, sl)
	Rheology	  *_Rh; // rheology coefficients (like Gamma, n, A, etc.)
	double  _C1, _C2; // C1 = dt / (2 dx), C2 = C1/dx;
	double       _ti; // initial time in a (years)
	double		   _tf; // final time in a

	// Numerics
	int 	  	 _Nx; // number of points (boundaries included)
	int			   _Ny;
	double 	 	 _dx; // space step in m
	double 	 	 _dt; // time step in a
	int		   _size; // number of time steps; gives the size of arrays H1, H2, H3, L1, L2, L3 and v
	bool    _store; // if true, then store all the thicknesses, for primal-dual computations; activated through routine Store()
	double	_tol; // tolerance for stationary computations

	// Linear System
	LinSystSIA3D *_ls;
	Grid _C1m; // various grids containing various quantities that arise in the linear system
	Grid _C1p;
	Grid _C2m;
	Grid _C2p;
	Grid  _DD;
	Grid _Gsx;
	Grid _Gsy;

	// Output
	OutputSIA3D *_O;
};

#endif /* FORWARDSIA3D_H_ */
