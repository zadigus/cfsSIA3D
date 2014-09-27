#include "Rheology.hpp"
#include <cmath>
#include <cassert>
#include "PhysicsCoreParams.hpp"

#include <iostream>

Rheology::Rheology(Component* aComponent, std::unique_ptr<PhysicsCoreParams>& aPhysCoreParams)
	: PhysicsComponent(aComponent)
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
	//_Gamma = 2 * _x[1] * pow(1e-5, _x[0])*_rhogn / (_x[0] + 2);
	_Gamma = 2 * A() *_rhogn / (n() + 2);
}

double Rheology::A()
{ 
	return _parameters["A"]*pow(1e-5, n()); 
}	

//void Rheology::Set(unsigned int i, double val) {
	//_x[i] = val;
	//if (i == 1) UpdateGamma(); // if A changes, then also Gamma
//}
