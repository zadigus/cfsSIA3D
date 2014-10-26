#include "Matrix.hpp"

namespace N_Mathematics {

	Matrix::Matrix(unsigned int MS) : m_MS(MS)
	{

	}

	Matrix::~Matrix()
	{

	}

	void Matrix::Clear()
	{
		m_NonZeroes.clear();
		m_ColIdx.clear();
		m_Values.clear();
	}

}