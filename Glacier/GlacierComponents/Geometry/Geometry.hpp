#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"

#include "Teuchos_RCP.hpp"

class Epetra_Vector;
class Grid;

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
      double b(std::size_t i, std::size_t j) const;
      double gradbx(std::size_t i, std::size_t j) const;
      double gradby(std::size_t i, std::size_t j) const;
      double H(std::size_t i, std::size_t j) const;
      double& H(std::size_t i, std::size_t j);

      void setH(const std::shared_ptr<Grid>& a_Grid);

      std::size_t Nx() const;
      std::size_t Ny() const;
      double Dx() const;
      double Dy() const;

    private: // TODO: probably not a good idea; maybe use the pImpl idiom here
			std::shared_ptr<Grid> m_b; // bedrock topography
			std::shared_ptr<Grid> m_H; // ice thickness
			std::shared_ptr<Grid> m_gradbx; // gradients of the bedrock topography wrt to x
			std::shared_ptr<Grid> m_gradby; // wrt to y
	};

  /*
   * Non-member methods
   */
  double staggeredGradSurfNorm(const Geometry& a_Geometry, std::size_t i, std::size_t j);

  void setThickness(Geometry& a_Geometry, const std::shared_ptr<Grid>& a_Grid);
  void setThickness(Geometry& a_Geometry, const Teuchos::RCP<Epetra_Vector>& a_Vector);
}
#endif /* GEOMETRY_H_ */
