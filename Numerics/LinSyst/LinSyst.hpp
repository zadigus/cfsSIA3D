#ifndef LINSYST_HPP_
#define LINSYST_HPP_

#include <vector>

namespace Mathematics {

	/*
	 * Abstract class for a linear system
	 */
	class LinSyst {
		public:
			explicit LinSyst(int MS);
			virtual ~LinSyst();

			virtual void AssembleMatrix(const std::vector<int>& aNonZeroes, const std::vector<int>& aColIdx, const std::vector<double>& aMatValues) = 0;
			virtual void AssembleRHS(const std::vector<double>& aRHSValues) = 0;
			virtual const std::vector<double>& Solve() = 0;
	};

}

#endif