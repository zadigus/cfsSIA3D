#include "Rheology.hpp"
#include <cmath>
#include <cassert>
#include "PhysicsCoreParams.hpp"

//#include <iostream>

namespace N_Glacier {

	Rheology::Rheology(std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams, N_Configuration::Component* aComponent)
		: GlacierComponent(aComponent)
		, _A(_parameters.find("A") != _parameters.end() ? std::stod(_parameters["A"]) : 0)
		, _n(_parameters.find("n") != _parameters.end() ? std::stod(_parameters["n"]) : 0)
		, _rho(aPhysCoreParams->rho_i())
		, _g(aPhysCoreParams->g())
	{

		_rhogn = pow(_rho*_g, n());
		UpdateGamma();
		assert(0 < n() && n() <= 3);
	}

	Rheology::~Rheology()
	{

	}

	void Rheology::UpdateGamma()
	{ // Gamma in consistent units
		_Gamma = 2 * A() *_rhogn / (n() + 2);
	}

	double Rheology::A()
	{
		return _A * pow(1e-5, n());
	}

}

//void Rheology::Set(unsigned int i, double val) {
	//_x[i] = val;
	//if (i == 1) UpdateGamma(); // if A changes, then also Gamma
//}
