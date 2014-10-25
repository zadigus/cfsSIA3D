#ifndef LINSYST_HPP_
#define LINSYST_HPP_

#include <vector>

namespace N_Mathematics {

	/*
	 * Abstract class for a linear system
	 */
	class LinSyst {
		public:
			explicit LinSyst(int MS);
			virtual ~LinSyst();

			virtual void AssembleMatrix(/*const std::vector<int>& aNonZeroes, const std::vector<int>& aColIdx, const std::vector<double>& aMatValues*/) = 0;
			virtual void AssembleRHS(/*const std::vector<double>& aRHSValues*/) = 0;
			virtual const std::vector<double>& Solve() = 0;

		protected:
			std::vector<int>    _NonZeroes; // TODO: create a CSR structure?
			std::vector<int>       _ColIdx;
			std::vector<double> _MatValues;
			std::vector<double> _RHSValues;
	};

}

#endif