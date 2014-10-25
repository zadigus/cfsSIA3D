#ifndef SLIDINGLAW_H_
#define SLIDINGLAW_H_

#include "Glacier/GlacierComponents/GlacierComponent.hpp"

#include <memory>
#include <vector>

class Grid;

namespace N_Glacier {

	class SlidingLaw : public GlacierComponent {
	public:
		SlidingLaw(N_Configuration::Component* aSlidingLaw = nullptr);
		//SlidingLaw();
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
