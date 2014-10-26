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
			unsigned int m_MS;
			std::vector<unsigned int>    m_NonZeroes;
			std::vector<unsigned int>       m_ColIdx;
			std::vector<double>             m_Values;
	};

	inline unsigned int Matrix::MS()
	{
		return m_MS;
	}

	inline void Matrix::InsertNonZeroes(unsigned int nnz)
	{
		m_NonZeroes.push_back(nnz);
	}

	inline void Matrix::InsertColIdx(unsigned int colIdx)
	{
		m_ColIdx.push_back(colIdx);
	}

	inline void Matrix::InsertValue(double val)
	{
		m_Values.push_back(val);
	}

}

#endif