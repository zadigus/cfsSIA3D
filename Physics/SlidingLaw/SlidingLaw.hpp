#ifndef SLIDINGLAW_H_
#define SLIDINGLAW_H_

#include "PhysicalComponent.hpp"

#include <memory>
#include <vector>

class Grid;

class SlidingLaw : public PhysicalComponent {
	public:
		SlidingLaw(unsigned int=0, unsigned int=0, double=0);
		virtual ~SlidingLaw();

		virtual void Generate(Grid &, unsigned int);

		// Computes the sliding coefficient on the staggered grid
		void Stagger(unsigned int);

		// Access to class members
		const double& operator()(const unsigned int, const unsigned int) const;

		// Data Export
		void Export(std::string) const;
		void ExportSL(std::string) const;

	protected:
		std::unique_ptr<Grid> 	_sl; // staggered sliding coefficients, , corresponds to (sc * 1e-5)^n.Staggered()
		std::unique_ptr<Grid> 	_sc; // sliding coefficients, corresponds to 1/C in Jouvet's notations, with e.g. C = 0.3 for Rhône glacier
};

#endif /* SLIDINGLAW_H_ */
