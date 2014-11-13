#include "Array2D.hpp"

#include <cassert>

Array2D::Array2D(int Nx, int Ny)
: m_Nx(Nx)
, m_Ny(Ny)
,	m_Data(new double[Nx*Ny]()) // initialize with zeroes
{

}

Array2D::~Array2D()
{

}

Array2D::Array2D(const Array2D& right) // produce a new object
: m_Nx(right.m_Nx)
, m_Ny(right.m_Ny)
, m_Data(new double[m_Nx*m_Ny])
{
	double* source(right.m_Data.get());
	double* dest(m_Data.get());
	std::copy(source, source + m_Nx*m_Ny, dest); // TODO: use STL range algorithm which can avoid doing a loop as it is done in the std::copy
}

Array2D& Array2D::operator=(const Array2D& right) // set an existing object
{
	m_Nx = right.m_Nx;
	m_Ny = right.m_Ny;

	m_Data.reset(new double[m_Nx*m_Ny]);
	double* source(right.m_Data.get());
	double* dest(m_Data.get());
	std::copy(source, source + m_Nx*m_Ny, dest);

	return *this;
}

void Array2D::Reset(int Nx, int Ny)
{
	m_Nx = Nx;
	m_Ny = Ny;
	m_Data.reset(new double[m_Nx*m_Ny]());
}

void Array2D::operator()()
{
	m_Data.reset(new double[m_Nx*m_Ny]()); // reset with zeroes 
}

double& Array2D::operator()(const int i, const int j)
{
	assert(0 <= i); assert(0 <= j);
	assert(i < m_Nx); assert(j < m_Ny);
	return m_Data[i*m_Ny + j];
}

Array2D& Array2D::operator+=(const Array2D& right)
{
	assert(right.m_Nx == m_Nx);
	assert(right.m_Ny == m_Ny);
	for (int i(0); i < m_Nx*m_Ny; ++i)
		m_Data[i] += right.m_Data[i];
	return *this;
}

Array2D& Array2D::operator-=(const Array2D& right)
{
	assert(right.m_Nx == m_Nx);
	assert(right.m_Ny == m_Ny);
	for (int i(0); i < m_Nx*m_Ny; ++i)
		m_Data[i] -= right.m_Data[i];
	return *this;
}

Array2D& Array2D::operator*=(double c)
{
	for (int i(0); i < m_Nx*m_Ny; ++i)
		m_Data[i] *= c;
	return *this;
}

Array2D operator+(const Array2D& left, const Array2D& right)
{
	//Array2D out(left);
	//out += right;
	//return out;
	return Array2D(left) += right;
}

Array2D operator-(const Array2D& left, const Array2D& right)
{
	/*Array2D out(left);
	out -= right;
	return out;*/
	return Array2D(left) -= right;
}

Array2D operator*(const Array2D& lhs, double rhs)
{
	return Array2D(lhs) *= rhs;
}

Array2D operator*(double lhs, const Array2D& rhs)
{
	return Array2D(rhs) *= lhs;
}

/*Array2D Array2D::operator*(const double c)
{
	//Array2D out(*this);
	//out *= c;
	//return out;
	return Array2D(*this) *= c;
}*/
