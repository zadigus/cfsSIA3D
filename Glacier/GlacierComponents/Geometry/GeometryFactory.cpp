#include "GeometryFactory.hpp"

#include "Configuration/ModelConfiguration.hpp"

#include "Geometry.hpp"

namespace N_Glacier {

	//Geometry* GeometryFactory::make(N_Configuration::Component* aGeometry)
	Geometry* GeometryFactory::make(const N_Configuration::Component& aGeometry)
	{ 
		return new Geometry(aGeometry);
	}

}