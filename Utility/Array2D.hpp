#ifndef ARRAY2D_H_
#define ARRAY2D_H_

#include <memory>
#include <vector>

class Array2D {
public:
	// Constructor / destructor
  Array2D(std::size_t Nrows=0, std::size_t Ncols=0);
	~Array2D();

	// Copy constructor / assignment operator
	Array2D(const Array2D&);
	Array2D& operator=(const Array2D&);

	// Getters
  std::size_t Nx() const { return m_Nx; }
  std::size_t Ny() const { return m_Ny; }
  double& operator()(std::size_t, std::size_t);
  double operator()(std::size_t, std::size_t) const;

	// Data handling
	Array2D& operator+=(const Array2D&);
	Array2D& operator-=(const Array2D&);
	Array2D& operator*=(double);

  void Reset(std::size_t Nrows, std::size_t Ncols);
private:
  unsigned int m_Nx;
  unsigned int m_Ny;
	std::vector<double> m_Data;
};

Array2D operator+(const Array2D&, const Array2D&);
Array2D operator-(const Array2D&, const Array2D&);
Array2D operator*(const Array2D&, double); // this is exactly the same Array2D operator*(double rhs)
Array2D operator*(double, const Array2D&); 

#endif
