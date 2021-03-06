#ifndef SLIDINGLAW_H_
#define SLIDINGLAW_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"

#include <memory>

class Grid;

namespace N_Glacier {

	class Geometry;

	// Interface for the sliding law
	class SlidingLaw : public GlacierComponent {
	public:
		SlidingLaw(const N_Configuration::Component& a_SlidingLaw);
		SlidingLaw();
		virtual ~SlidingLaw();

		void Generate(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp); // that method must be called outside the ctor, because it calls virtual methods

		// Access to class members
    const double& operator()(size_t, size_t) const;

		// Data Export
    void Export(std::string) const;
		void ExportSL(std::string) const;

	protected:
		// Compute the sliding coefficient on the staggered grid
		virtual void Init(const std::shared_ptr<Geometry>& a_Geometry); // initialization of _sl and _sc
		virtual void Fill(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp) = 0; // the sliding coefficient depends on the bedrock topography
		virtual void Stagger(double a_GlenExp); // build staggered grid

	private:
		SlidingLaw(const SlidingLaw&); // not implemented
		SlidingLaw& operator=(const SlidingLaw&); // not implemented

	protected:
		std::unique_ptr<Grid> 	m_sl; // staggered sliding coefficients, , corresponds to (sc * 1e-5)^n.Staggered()
		std::unique_ptr<Grid> 	m_sc; // sliding coefficients, corresponds to 1/C in Jouvet's notations, with e.g. C = 0.3 for Rhône glacier
	};

}

#endif /* SLIDINGLAW_H_ */
