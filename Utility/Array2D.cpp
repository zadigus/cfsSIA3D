#include "Array2D.hpp"

#include <algorithm>
#include <functional>
#include <cassert>

Array2D::Array2D(int Nx, int Ny)
: m_Nx(Nx)
, m_Ny(Ny)
, m_Data(Nx*Ny, 0)
{

}

Array2D::~Array2D()
{

}

Array2D::Array2D(const Array2D& right) // produce a new object
: m_Nx(right.m_Nx)
, m_Ny(right.m_Ny)
, m_Data(right.m_Data)
{

}

Array2D& Array2D::operator=(const Array2D& right) // set an existing object
{
	m_Nx = right.m_Nx;
	m_Ny = right.m_Ny;
	m_Data = right.m_Data;

	return *this;
}

/*void Array2D::Reset(int Nx, int Ny) // TODO: Do I really need such a method?
{
	m_Nx = Nx;
	m_Ny = Ny;

	//m_Data.

	m_Data.reset(new double[m_Nx*m_Ny]());
}*/

/*void Array2D::operator()()
{
	m_Data.reset(new double[m_Nx*m_Ny]()); // reset with zeroes 
}*/

double& Array2D::operator()(const int i, const int j)
{
	return m_Data.at(i*m_Ny + j);
}

Array2D& Array2D::operator+=(const Array2D& right)
{
	assert(right.m_Nx == m_Nx);
	assert(right.m_Ny == m_Ny);
	std::transform(m_Data.begin(), m_Data.end(), right.m_Data.begin(), m_Data.begin(), std::plus<double>());
	return *this;
}

Array2D& Array2D::operator-=(const Array2D& right)
{
	assert(right.m_Nx == m_Nx);
	assert(right.m_Ny == m_Ny);
	std::transform(m_Data.begin(), m_Data.end(), right.m_Data.begin(), m_Data.begin(), std::minus<double>());
	return *this;
}

Array2D& Array2D::operator*=(double c)
{
	std::transform(m_Data.begin(), m_Data.end(), m_Data.begin(), std::bind(std::multiplies<double>(), std::placeholders::_1, c));
	return *this;
}

Array2D operator+(const Array2D& left, const Array2D& right)
{
	return Array2D(left) += right;
}

Array2D operator-(const Array2D& left, const Array2D& right)
{
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
