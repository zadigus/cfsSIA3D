#ifndef LINSYST_HPP_
#define LINSYST_HPP_

#include <vector>
#include <memory>

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class Matrix;
	class Vector;

	/*
	 * Abstract class for a linear system A * x = b
	 */
	class LinSyst {
		public:
			explicit LinSyst(N_Configuration::Component* aLinSyst = nullptr); // TODO: define SUBComponents (e.g. for Component Diffusion, define SubComponent LinSyst)
			virtual ~LinSyst();

			virtual const Vector& Solve() = 0;

			// Getters
			unsigned int MS();
			void SetMatrix(std::unique_ptr<Matrix> Mat);
			void SetRHS(std::unique_ptr<Vector> RHS);

		protected:
			std::unique_ptr<Matrix> m_A;
			std::unique_ptr<Vector> m_b;
	};

}

#endif