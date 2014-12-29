#include "EpetraVector.hpp"
#include "Epetra_Vector.h"
#include "Epetra_Map.h"

namespace N_Mathematics {

	EpetraVector::EpetraVector(const Epetra_Map& aMap)
		: IVector()
	{
		m_Data.reset(new Epetra_Vector(aMap));
	}

	EpetraVector::~EpetraVector()
	{

	}

	double& EpetraVector::operator[](unsigned int i)
	{
		return (*m_Data)[i];
	}

	int EpetraVector::size()
	{
		return m_Data->Map().NumGlobalElements();
	}

}