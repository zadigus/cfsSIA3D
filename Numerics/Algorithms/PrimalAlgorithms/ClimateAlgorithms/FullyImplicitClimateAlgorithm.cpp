#include "FullyImplicitClimateAlgorithm.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include "Glacier/Glacier.hpp"
#include "Glacier/GlacierComponents/MassBalance/MassBalance.hpp"
#include "NumericsCoreParams.hpp"

namespace N_Mathematics {

	FullyImplicitClimateAlgorithm::FullyImplicitClimateAlgorithm(const std::unique_ptr<NumericsCoreParams>& aNumCoreParams, N_Configuration::Component* aClimateAlgo)
		: PrimalAlgorithm(aClimateAlgo)
		, _H(_glacier->H())
		, _Hn(new Grid(*_H)) // initialization of Newton process
		, _b(_glacier->b())
		, _B(_glacier->B())
		, _err(1)
		, _tol(_parameters.find("tol") != _parameters.end() ? std::stod(_parameters["tol"]) : 1e-6)
		, _updt(0) 
		, _F(0) 
		, _Fp(0) 
		, _dt(aNumCoreParams->dt())
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
				for (unsigned int j(0); j<_H->Ny(); ++j) { // TODO: try to write that as a linear system
					// TODO: integrate constantMB; it should be possible to access B with x, y too
					_F = (*_Hn)(i, j) - (*_H)(i, j) - _dt*(*_B)((*_b)(i, j), (*_Hn)(i, j), (*_H)(i, j)); 
					_Fp = 1 - _dt*_B->dB((*_b)(i, j), (*_Hn)(i, j), (*_H)(i, j)); // derivative of mass balance wrt glacier surface
					_updt = _F / _Fp; (*_Hn)(i, j) -= _updt;
					if (fabs(_updt) > _err) _err = fabs(_updt);
				}
			}
		}

		*_H = *_Hn;
	}

}