#ifndef MATHEMATICS_MATRIX_HPP_
#define MATHEMATICS_MATRIX_HPP_

#include <vector>

namespace N_Mathematics {

	/*
	 * Square matrix stored in compressed storage row format (CSR)
	 */

	class Matrix
	{
		public:
			Matrix(unsigned int MS);
			virtual ~Matrix();

			unsigned int MS();
			void InsertNonZeroes(unsigned int nnz);
			void InsertColIdx(unsigned int colIdx);
			void InsertValue(double val);
			void Clear();

		protected:
			unsigned int _MS;
			std::vector<unsigned int>    _NonZeroes;
			std::vector<unsigned int>       _ColIdx;
			std::vector<double>             _Values;
	};

	inline unsigned int Matrix::MS()
	{
		return _MS;
	}

	inline void Matrix::InsertNonZeroes(unsigned int nnz)
	{
		_NonZeroes.push_back(nnz);
	}

	inline void Matrix::InsertColIdx(unsigned int colIdx)
	{
		_ColIdx.push_back(colIdx);
	}

	inline void Matrix::InsertValue(double val)
	{
		_Values.push_back(val);
	}

}

#endif