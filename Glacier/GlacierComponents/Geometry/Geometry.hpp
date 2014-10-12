#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"
//#include "GlacierComponent.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier { 

	struct PhysicsCoreParams;

	// Interface class for mass-balance data
	class Geometry : public GlacierComponent {
		public:
			Geometry(N_Configuration::Component* aComponent = nullptr);
			virtual ~Geometry();
			
			std::shared_ptr<Grid> b();
			std::shared_ptr<Grid> H();

			//void print() { std::cout << "H.Dx = " << _H->Dx() << std::endl; }

		private:
			std::shared_ptr<Grid> _b; // bedrock topography
			std::shared_ptr<Grid> _H; // ice thickness
	};
	
	inline std::shared_ptr<Grid> Geometry::b()
	{
		return _b;
	}

	inline std::shared_ptr<Grid> Geometry::H()
	{
		return _H;
	}

}
#endif /* GEOMETRY_H_ */
