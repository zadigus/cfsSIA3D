#include "Matrix.hpp"

namespace N_Mathematics {

	Matrix::Matrix(unsigned int MS) : _MS(MS)
	{

	}

	Matrix::~Matrix()
	{

	}

	void Matrix::Clear()
	{
		_NonZeroes.clear();
		_ColIdx.clear();
		_Values.clear();
	}

}