#ifndef MATHEMATICS_EPETRAMATRIX_HPP_
#define MATHEMATICS_EPETRAMATRIX_HPP_

//#include <vector>
#include <memory>
#include "IMatrix.hpp"

class Epetra_CrsMatrix;

namespace N_Mathematics {

	/*
	 * Epetra square matrix
	 */

	class EpetraMatrix : public IMatrix
	{
		public:
			EpetraMatrix(std::vector<int>&& aNnz, std::vector<int>&& aColIdx);
			virtual ~EpetraMatrix();

			int setRow(int aRowNb, const std::vector<double>& aValues, const std::vector<int>& aColIdx);
			
			std::shared_ptr<Epetra_CrsMatrix> get();
			int MS();

		private:
			std::shared_ptr<Epetra_CrsMatrix> m_Data;
	};

}

#endif