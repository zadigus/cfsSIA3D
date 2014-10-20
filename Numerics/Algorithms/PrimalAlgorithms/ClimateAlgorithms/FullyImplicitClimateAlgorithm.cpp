#include "FullyImplicitClimateAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/Glacier.hpp"
#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(N_Configuration::Component* aClimateAlgo)
		: PrimalAlgorithm(aClimateAlgo)
		, _H(_glacier->H())
		, _Hn(new Grid(*_H)) // initialization of Newton process
		, _b(_glacier->b())
		, _B(_glacier->B())
		, _err(1)
		, _tol(1e-6) // TODO: leave that in aClimateAlgo
		, _updt(0) // TODO: put these comments in the header; opposite of Newton iteration update = -(x^{k+1}-x^{k}) = F / Fp
		, _F(0) // value of the function we seek the zero of
		, _Fp(0) // value of the derivative of F
	{

	}

	FullyImplicitClimateAlgorithm::~FullyImplicitClimateAlgorithm()
	{

	}

	void FullyImplicitClimateAlgorithm::Run()
	{
		while (_err > _tol) {
			_err = 0;
			for (unsigned int i(0); i<_H->Nx(); ++i) {
				for (unsigned int j(0); j<_H->Ny(); ++j) {
					// TODO: integrate constantMB; it should be possible to access B with x, y too
					_F = (*_Hn)(i, j) - (*_H)(i, j) - _dt*(*_B)(_fs(i, j), _HN(i, j), _H(i, j)); // TODO: add _dt in a NumericsCore.xml
					_Fp = 1 - _dt*_B->ds(_fs(i, j), _HN(i, j), _H(i, j)); // derivative of mass balance wrt glacier surface
					_updt = _F / _Fp; _HN(i, j) -= _updt;
					if (fabs(_updt) > _err) _err = fabs(_updt);
				}
			}
		}
		_H.Import(_HN);
	}

}