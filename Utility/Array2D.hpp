#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include <memory>
#include <vector>

class Array2D {
public:
	// Constructor / destructor
	Array2D(int Nrows=0, int Ncols=0);
	~Array2D();

	// Copy constructor / assignment operator
	Array2D(const Array2D&);
	Array2D& operator=(const Array2D&);

	// Getters
	int Nx() const { return m_Nx; }
	int Ny() const { return m_Ny; }
	double& operator()(const int, const int);

	// Data handling
	Array2D& operator+=(const Array2D&);
	Array2D& operator-=(const Array2D&);
	Array2D& operator*=(double);

	void Reset(int Nrows, int Ncols);
private:
	int m_Nx;
	int m_Ny;
	std::vector<double> m_Data;
};

Array2D operator+(const Array2D&, const Array2D&);
Array2D operator-(const Array2D&, const Array2D&);
Array2D operator*(const Array2D&, double); // this is exactly the same Array2D operator*(double rhs)
Array2D operator*(double, const Array2D&); 

#endif
