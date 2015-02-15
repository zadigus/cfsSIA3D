#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"
#include "Numerics/Mesh/Grid.hpp"

#include <iostream>

namespace N_Glacier { 

	struct PhysicsCoreParams;

	// Interface class for geometry data
	class Geometry : public GlacierComponent {
		public:
			// constructors/destructors
			Geometry(const N_Configuration::Component& a_Component);
			virtual ~Geometry();
			Geometry(const Geometry& a_Geometry);
			Geometry& operator=(const Geometry& a_Geometry);

    public:
      // public members
      double b(unsigned int i, unsigned int j);
      double gradbx(unsigned int i, unsigned int j);
      double gradby(unsigned int i, unsigned int j);
      double& H(unsigned int i, unsigned int j);

      void setH(const std::shared_ptr<Grid>& a_H);
      double staggeredGradSurfNorm(unsigned int i, unsigned int j);

			unsigned int Nx();
			unsigned int Ny();
			double Dx();
			double Dy();

		private:
			std::shared_ptr<Grid> m_b; // bedrock topography
			std::shared_ptr<Grid> m_H; // ice thickness
			std::shared_ptr<Grid> m_gradbx; // gradients of the bedrock topography wrt to x
			std::shared_ptr<Grid> m_gradby; // wrt to y
	};

	inline void Geometry::setH(const std::shared_ptr<Grid>& a_H)
	{
		m_H = a_H;
	}

}
#endif /* GEOMETRY_H_ */
