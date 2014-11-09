#include "Vector.hpp"

#include "Numerics/Mesh/Grid.hpp"

namespace N_Mathematics {

	Vector::Vector(unsigned int MS) : m_MS(MS)
	{

	}

	Vector::~Vector()
	{

	}

	void Vector::toGrid(std::shared_ptr<Grid>& aGrid)
	{
		unsigned int I(0);

		for (unsigned int i(0); i < aGrid->Nx(); ++i)  // TODO: maybe fill the matrix in the same order as the Grid ctor; it will be easier to do the conversion between Vector and Grid
		{ // update the way the linear system matrix is filled
			for (unsigned int j(0); j < aGrid->Ny(); ++j)
			{
				(*aGrid)(i, j) = m_Values.at(I++);
			}
		}
	}

}