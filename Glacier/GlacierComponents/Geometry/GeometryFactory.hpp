#ifndef GEOMETRYFACTORY_H_
#define GEOMETRYFACTORY_H_

#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	
	class Geometry;

	class GeometryFactory
	{
		public:
			// factory methods
			//static Geometry* make(N_Configuration::Component* aGeometry = nullptr);
			static Geometry* make(const N_Configuration::Component& aGeometry);
		};

}

#endif