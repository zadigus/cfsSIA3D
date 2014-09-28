#ifndef SLIDINGLAW_H_
#define SLIDINGLAW_H_

#include "PhysicsComponent.hpp"

#include <memory>
#include <vector>

class Grid;
//class Component;

namespace N_Physics {

	class SlidingLaw : public PhysicsComponent {
	public:
		SlidingLaw(Component* aSlidingLaw/*, unsigned int=0, unsigned int=0, double=0*/);
		SlidingLaw();
		virtual ~SlidingLaw();

		void Generate(Grid&, unsigned int); // TODO: double-check that this routine is always called in the code (after the constructor)

		// Access to class members
		const double& operator()(const unsigned int, const unsigned int) const;

		// Data Export
		void Export(std::string) const;
		void ExportSL(std::string) const;

	protected:
		// Compute the sliding coefficient on the staggered grid
		virtual void Init(const Grid&); // initialization of _sl and _sc
		virtual void Fill(Grid&, unsigned int); // the sliding coefficient depends on the bedrock topography
		virtual void Stagger(unsigned int); // build staggered grid
		// TODO: double check with Grid::Staggered

	protected:
		std::unique_ptr<Grid> 	_sl; // staggered sliding coefficients, , corresponds to (sc * 1e-5)^n.Staggered()
		std::unique_ptr<Grid> 	_sc; // sliding coefficients, corresponds to 1/C in Jouvet's notations, with e.g. C = 0.3 for Rhône glacier
	};

}

#endif /* SLIDINGLAW_H_ */