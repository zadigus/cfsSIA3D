#ifndef MATHEMATICS_EPETRAVECTOR_HPP_
#define MATHEMATICS_EPETRAVECTOR_HPP_

#include "IVector.hpp"

#include <memory>

class Epetra_Vector;
class Epetra_Map;

namespace N_Mathematics {

	class EpetraVector : public IVector
	{
		public:
			EpetraVector(const Epetra_Map& aMap);
			virtual ~EpetraVector();

			double& operator[](unsigned int i);

			int size();
	
		private:
			std::shared_ptr<Epetra_Vector> m_Data;
	};
}

#endif