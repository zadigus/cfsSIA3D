#ifndef MATHEMATICS_IMATRIX_HPP_
#define MATHEMATICS_IMATRIX_HPP_

#include <vector>

namespace N_Mathematics {

	/*
	 *   Square matrix stored in compressed storage row format (CSR)
	 *   This is an adapter interface class
	 */

	class IMatrix
	{
		public:
			IMatrix();
			virtual ~IMatrix();

			/*
			 *  Set matrix row
			 *  Caution: this method must only access the elements available in the CRS structure otherwise it must throw an error
			 */
			virtual int setRow(int aRowNb, const std::vector<double>& aValues, const std::vector<int>& aColIdx) = 0;

			virtual int MS() = 0;
	};

}

#endif