#include "LinSyst.hpp"

#include "Matrix.hpp"
#include "Vector.hpp"

#include "Configuration/ModelConfiguration.hpp"

namespace N_Mathematics {

	LinSyst::LinSyst(N_Configuration::SubComponent* aLinSyst)
		: m_A(nullptr)
		, m_b(nullptr)
		, m_X(nullptr)
	{
	
	}

	LinSyst::~LinSyst()
	{

	}

	unsigned int LinSyst::MS()
	{
		return m_A->MS();
	}
	
	void LinSyst::SetMatrix(std::unique_ptr<Matrix> Mat)
	{
		m_A.reset(Mat.release());
	}

	void LinSyst::SetRHS(std::unique_ptr<Vector> RHS)
	{
		m_b.reset(RHS.release());
	}

	std::shared_ptr<Vector> LinSyst::getSolution()
	{
		return m_X;
	}

}