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
			explicit LinSyst(unsigned int MS, N_Configuration::Component* aLinSyst = nullptr); // TODO: define SUBComponents (e.g. for Component Diffusion, define SubComponent LinSyst)
			virtual ~LinSyst();

			virtual const Vector& Solve() = 0;

			// Getters
			unsigned int MS();
			std::shared_ptr<Matrix> Mat();
			std::shared_ptr<Vector> RHS();

		protected:
			std::shared_ptr<Matrix> _A;
			std::shared_ptr<Vector> _b;
	};

	inline std::shared_ptr<Matrix> LinSyst::Mat()
	{
		return _A;
	}

	inline std::shared_ptr<Vector> LinSyst::RHS()
	{
		return _b;
	}

}

#endif