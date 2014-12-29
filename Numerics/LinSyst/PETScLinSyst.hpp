#ifndef PETSCLINSYST_H_
#define PETSCLINSYST_H_

#include <vector>

#include "LinSyst.hpp"
#include "petsc.h"

namespace N_Configuration {
	class SubComponent;
}

namespace N_Mathematics {

	// Linear system using the PETSc library

	class PETScLinSyst : public LinSyst
	{
		public:
			PETScLinSyst(N_Configuration::SubComponent* aLinSyst, int aMS);
			~PETScLinSyst();

			// Solving linear system
			//void SetIterative();
			void Solve();

		private:
			/*// Access to class members
			double	*Get()			{ double *x; VecGetArray(_X, &x); return x; }
			void 	Restore(double *x) 	{ VecRestoreArray(_X, &x); }*/

		private:
			Vec m_b, m_X;
			Mat m_A;
			KSP m_Solver;
			
			KSPConvergedReason m_Reason;
	};

}

#endif /* PETSCLINSYST_H_ */
