#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier { 

	struct PhysicsCoreParams;

	// Interface class for mass-balance data
	class Geometry : public GlacierComponent {
		public:
			//Geometry(N_Configuration::Component* aComponent = nullptr);
			Geometry(const N_Configuration::Component& aComponent);
			virtual ~Geometry();
			
			std::shared_ptr<Grid> b();
			std::shared_ptr<Grid> H();
			std::shared_ptr<Grid> gradbx();
			std::shared_ptr<Grid> gradby();

		private:
			std::shared_ptr<Grid> m_b; // bedrock topography
			std::shared_ptr<Grid> m_H; // ice thickness
			std::shared_ptr<Grid> m_gradbx; // gradients of the bedrock topography wrt to x
			std::shared_ptr<Grid> m_gradby; // wrt to y
	};
	
	inline std::shared_ptr<Grid> Geometry::b()
	{
		return m_b;
	}

	inline std::shared_ptr<Grid> Geometry::H()
	{
		return m_H;
	}

	inline std::shared_ptr<Grid> Geometry::gradbx()
	{
		return m_gradbx;
	}

	inline std::shared_ptr<Grid> Geometry::gradby()
	{
		return m_gradby;
	}

}
#endif /* GEOMETRY_H_ */
