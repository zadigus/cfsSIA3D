#include "Array2D.hpp"

#include <cassert>

Array2D::Array2D(int Nx, int Ny)
: _Nx(Nx)
, _Ny(Ny)
,	_Data(new double[Nx*Ny]()) // initialize with zeroes
{

}

Array2D::~Array2D()
{

}

Array2D::Array2D(const Array2D& right) // produce a new object
: _Nx(right._Nx)
, _Ny(right._Ny)
, _Data(new double[_Nx*_Ny])
{
	double* source(right._Data.get());
	double* dest(_Data.get());
	std::copy(source, source + _Nx*_Ny, dest);
}

Array2D& Array2D::operator=(const Array2D& right) // set an existing object
{
	assert(_Nx == right._Nx);
	assert(_Ny == right._Ny);

	_Data.reset(new double[_Nx*_Ny]);
	double* source(right._Data.get());
	double* dest(_Data.get());
	std::copy(source, source + _Nx*_Ny, dest);

	return *this;
}

void Array2D::Reset(int Nx, int Ny)
{
	_Nx = Nx;
	_Ny = Ny;
	_Data.reset(new double[_Nx*_Ny]());
}

void Array2D::operator()()
{
	_Data.reset(new double[_Nx*_Ny]()); // reset with zeroes 
}

double& Array2D::operator()(const int i, const int j)
{
	assert(0 <= i); assert(0 <= j);
	assert(i < _Nx); assert(j < _Ny);
	return _Data[i*_Ny + j];
}

Array2D& Array2D::operator+=(const Array2D& right)
{
	assert(right._Nx == _Nx);
	assert(right._Ny == _Ny);
	for (int i(0); i < _Nx*_Ny; i++)
		_Data[i] += right._Data[i];
	return *this;
}

Array2D& Array2D::operator-=(const Array2D& right)
{
	assert(right._Nx == _Nx);
	assert(right._Ny == _Ny);
	for (int i(0); i < _Nx*_Ny; i++)
		_Data[i] -= right._Data[i];
	return *this;
}

Array2D& Array2D::operator*=(double c)
{
	for (int i(0); i < _Nx*_Ny; i++)
		_Data[i] *= c;
	return *this;
}

Array2D operator+(const Array2D& left, const Array2D& right)
{
	Array2D out(left);
	out += right;
	return out;
}

Array2D operator-(const Array2D& left, const Array2D& right)
{
	Array2D out(left);
	out -= right;
	return out;
}

Array2D Array2D::operator*(const double c)
{
	Array2D out(*this);
	out *= c;
	return out;
}