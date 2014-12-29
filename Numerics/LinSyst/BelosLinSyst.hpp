#ifndef BELOSLINSYST_H_
#define BELOSLINSYST_H_

#include "LinSyst.hpp"

namespace N_Configuration {
	class SubComponent;
}

namespace N_Mathematics {

	// Linear system using the Trilinos::Belos library

	class EpetraVector;
	class EpetraMatrix;
	class IVector;

	class BelosLinSyst : public LinSyst
	{
		public:
			BelosLinSyst(N_Configuration::SubComponent* aLinSyst);
			~BelosLinSyst();

			void setCrs(std::vector<int>&& aNnz, std::vector<int>&& aColIdx);

			std::shared_ptr<IMatrix> getMatrix();
			std::shared_ptr<IVector> getRHS();

			/*// Access to class members
			int 	MS() 					{ return _MS; }
			double	*Get()			{ double *x; VecGetArray(_X, &x); return x; }
			void 	Restore(double *x) 	{ VecRestoreArray(_X, &x); }*/

			// Solving linear system
			//void SetIterative();
			void solve();

			int MS();
			std::shared_ptr<IVector> getSolution();

		private:
			std::shared_ptr<EpetraMatrix> m_A;
			std::shared_ptr<EpetraVector> m_b;
			std::shared_ptr<EpetraVector> m_X;

		/*	Vec _b, _X;
			Mat _A;
			KSP _solver;
			
			KSPConvergedReason _reason;*/
	};

}

#endif /* BELOSLINSYST_H_ */
