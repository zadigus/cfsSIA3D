#ifndef LINSYST_HPP_
#define LINSYST_HPP_

//#include <vector>
#include <memory>

#include "Numerics/LinSyst/Vector.hpp"

namespace N_Configuration {
	class SubComponent;
}

namespace N_Mathematics {

	class Matrix;
	class Vector;

	/*
	 * Abstract class for a linear system A * x = b
	 */
	class LinSyst {
		public:
			explicit LinSyst(N_Configuration::SubComponent* aLinSyst = nullptr);
			virtual ~LinSyst();

			virtual void Solve() = 0;

			// Getters / Setters
			unsigned int MS();
			void SetMatrix(std::unique_ptr<Matrix> Mat);
			void SetRHS(std::unique_ptr<Vector> RHS);
			Vector getSolution();

		protected:
			std::unique_ptr<Matrix> m_A;
			std::unique_ptr<Vector> m_b;
	};

}

#endif