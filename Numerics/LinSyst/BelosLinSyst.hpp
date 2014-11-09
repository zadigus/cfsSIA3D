#ifndef BELOSLINSYST_H_
#define BELOSLINSYST_H_

#include <vector>

#include "LinSyst.hpp"
//#include "petsc.h"

namespace N_Configuration {
	class SubComponent;
}

namespace N_Mathematics {

	// Linear system using the Trilinos::Belos library

	class BelosLinSyst : public LinSyst
	{
		public:
			BelosLinSyst(N_Configuration::SubComponent* aLinSyst = nullptr); // TODO: think about what default parameters to set when no config exists
			~BelosLinSyst();

			/*// Access to class members
			int 	MS() 					{ return _MS; }
			double	*Get()			{ double *x; VecGetArray(_X, &x); return x; }
			void 	Restore(double *x) 	{ VecRestoreArray(_X, &x); }*/

			// Solving linear system
			//void SetIterative();
			void Solve();

		private:
		/*	Vec _b, _X;
			Mat _A;
			KSP _solver;
			
			KSPConvergedReason _reason;*/
	};

}

#endif /* BELOSLINSYST_H_ */
