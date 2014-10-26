#ifndef PETSCLINSYST_H_
#define PETSCLINSYST_H_

#include <vector>

#include "LinSyst.hpp"
#include "petsc.h"

namespace N_Mathematics {

	// Linear system using the PETSc library

	class PETScLinSyst : public LinSyst
	{
		public:
			PETScLinSyst(unsigned int MS, N_Configuration::Component* aLinSyst = nullptr); // TODO: think about what default parameters to set when no config exists
			~PETScLinSyst();

			// Solving linear system
			//void SetIterative();
			const Vector& Solve();

		private:
			/*// Access to class members
			double	*Get()			{ double *x; VecGetArray(_X, &x); return x; }
			void 	Restore(double *x) 	{ VecRestoreArray(_X, &x); }*/

		private:
			Vec _b, _X;
			Mat _A;
			KSP _solver;
			
			KSPConvergedReason _reason;
	};

}

#endif /* PETSCLINSYST_H_ */
