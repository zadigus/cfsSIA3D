#ifndef FINITEDIFFERENCEPRIMALALGORITHM_HPP_
#define FINITEDIFFERENCEPRIMALALGORITHM_HPP_

#include "PrimalAlgorithm.hpp"

class Grid;

namespace N_Configuration {
	class Component;
}

namespace N_Mathematics {

	class Vector;

	class FiniteDifferencePrimalAlgorithm : public PrimalAlgorithm
	{
		public:
			FiniteDifferencePrimalAlgorithm(N_Configuration::Component* aFiniteDifferenceAlgo);
			virtual ~FiniteDifferencePrimalAlgorithm();

			virtual void run() = 0;

		protected:
			// Access the geometry in a "natural" way
			double& H(unsigned int i, unsigned int j); // read & write
			double b(unsigned int i, unsigned int j);  // read only
			double gradbx(unsigned int i, unsigned int j);
			double gradby(unsigned int i, unsigned int j);

			// convert a Vector into a Grid
			virtual void Vector2Grid(const std::shared_ptr<Vector>& aVector, const std::shared_ptr<Grid>& aGrid); // can't be a Grid ctor, because the behavior of this method depends on how users fill their matrix

		protected:
			// Ice thickness
			std::shared_ptr<Grid> m_H;

			// Numerics parameters
			unsigned int m_Nx;
			unsigned int m_Ny;
			double m_Dx;

		private:
			// Bedrock topography
			std::shared_ptr<Grid> m_b;
			std::shared_ptr<Grid> m_gradbx;
			std::shared_ptr<Grid> m_gradby;
	};

}

#endif