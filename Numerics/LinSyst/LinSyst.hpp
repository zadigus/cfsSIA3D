#ifndef LINSYST_HPP_
#define LINSYST_HPP_

//#include <memory>
#include <vector>

#include "Teuchos_RCP.hpp"

namespace N_Configuration {
	class SubComponent;
}

class Epetra_CrsMatrix;
class Epetra_Vector;
class Epetra_SerialComm;
class Epetra_CrsGraph;

namespace N_Mathematics {

	/*
     * Class for a linear system A * x = b, where A is a square matrix
	 */
	class LinSyst {
		public:
            explicit LinSyst(const N_Configuration::SubComponent& aLinSyst);
            ~LinSyst();

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
             * The matrix structure cannot be changed any more after that method has been called
			 */
            void setCrs(std::vector<int>&& aNnz, std::vector<int>&& aColIdx);

            void solve();

            int matrixSize();
            Teuchos::RCP<Epetra_CrsMatrix> getMatrix();
            Teuchos::RCP<Epetra_Vector> getRHS();
            Teuchos::RCP<Epetra_Vector> getSolution();

        private:
            Teuchos::RCP<Epetra_CrsGraph> createCrsGraph(std::vector<int>&& aNnz, std::vector<int>&& aColIdx);

        private:
            // Matrix system
            Teuchos::RCP<Epetra_CrsMatrix> m_A;
            Teuchos::RCP<Epetra_Vector> m_b;
            Teuchos::RCP<Epetra_Vector> m_X;

            // Communications
            Teuchos::RCP<Epetra_SerialComm> m_Comm;
	};

    inline Teuchos::RCP<Epetra_CrsMatrix> LinSyst::getMatrix()
    {
        return m_A;
    }

    inline Teuchos::RCP<Epetra_Vector> LinSyst::getRHS()
    {
        return m_b;
    }

    inline Teuchos::RCP<Epetra_Vector> LinSyst::getSolution()
    {
        return m_X;
    }

}

#endif
