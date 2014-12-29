#ifndef LINSYST_HPP_
#define LINSYST_HPP_

#include <memory>
#include <vector>

namespace N_Configuration {
	class SubComponent;
}

namespace N_Mathematics {

	class IMatrix;
	class IVector;

	/*
	 * Abstract class for a linear system A * x = b, where A is a square matrix
	 */
	class LinSyst {
		public:
			explicit LinSyst(N_Configuration::SubComponent* aLinSyst);
			virtual ~LinSyst();

			/*
			 * Set the Compressed Row Storage (CRS) of the linear system's matrix
			 *  aNnz   : vector that holds the number of non-zero entries in each row
			 *  aColIdx: vector that holds the indices of the columns containing a non-zero value
			 *  For example, matrix
			 *  (1 0 0
			 *   2 0 3 
			 *   4 5 6)
			 *  is defined by
			 *  aNnz    = {0, 1, 3, 6}, and 6 is the amount of non-zero values in the matrix
			 *  aColIdx = {0, 0, 2, 0, 1, 2}
			 */
			virtual void setCrs(std::vector<int>&& aNnz, std::vector<int>&& aColIdx) = 0;

			virtual void solve() = 0;

			virtual int MS() = 0;
			virtual std::shared_ptr<IMatrix> getMatrix() = 0;
			virtual std::shared_ptr<IVector> getRHS() = 0;
			virtual std::shared_ptr<IVector> getSolution() = 0;
	};

}

#endif