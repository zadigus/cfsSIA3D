#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include <memory>

class Array2D {
public:
	// Constructor / destructor
	Array2D(int=0, int=0);
	~Array2D();

	// Copy constructor / assignment operator
	Array2D(const Array2D&);
	Array2D& operator=(const Array2D&);

	// Getters
	int Nx() const { return _Nx; }
	int Ny() const { return _Ny; }
	double& operator()(const int, const int);

	// Data handling
	void operator()();
	Array2D& operator+=(const Array2D&);
	Array2D& operator-=(const Array2D&);
	Array2D& operator*=(double);
	Array2D operator*(const double);

	friend Array2D operator+(const Array2D&, const Array2D&);
	friend Array2D operator-(const Array2D&, const Array2D&);

	void Reset(int, int);
private:
	int _Nx;
	int _Ny;
	std::unique_ptr<double[]> _Data;
};

#endif