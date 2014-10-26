#include "LinSyst.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	LinSyst::LinSyst(unsigned int MS, N_Configuration::Component* aLinSyst)
		: _A(nullptr)
		, _b(nullptr)
	{
	
	}

	LinSyst::~LinSyst()
	{

	}

	unsigned int LinSyst::MS()
	{
		return _A->MS();
	}
	

}