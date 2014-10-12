#include "Geometry.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier {

	Geometry::Geometry(N_Configuration::Component* aComponent)
		: GlacierComponent(aComponent)
		, _b(new Grid(_parameters["bed"]))
	{
		Grid s(_parameters["surface"]);
		_H.reset(new Grid(s-*_b));
	}

	Geometry::~Geometry() 
	{
	
	}
	
}