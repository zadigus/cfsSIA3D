#ifndef GRID_H_
#define GRID_H_

#include <memory>
#include <string>
#include <vector>

#include "Utility/Array2D.hpp"
#include "SpaceParams.hpp"

class Grid{
	public: 
		// Constructors / destructors
		Grid(unsigned int Nx = 0, unsigned int Ny = 0, double Dx = 0, double Dy = 0, double Xll = 0, double Yll = 0);
		Grid(std::string FileName);
		~Grid();

		// Copy constructor and assignment operator
		Grid(const Grid &);
		Grid& operator=(const Grid &);

		// Getters
    unsigned int Nx() const;
    unsigned int Ny() const;
    double Dx()	const;
    double Dy()	const;
    double Xll() const;
    double Yll() const;
    double  X(unsigned int i) const;
    double  Y(unsigned int j) const;
    bool IsData(unsigned int i, unsigned int j) const;
    double NoData() const;

		// Data handling
		//void Clear();
    void Refine(double ratio);
    void Refine(double ratioX, double ratioY);

    double& operator()(const unsigned int i, const unsigned int j) const;
    /*
     *  Interpolates the value of the grid elevation at position (x, y)
     *  Coordinates x and y must be expressed in global coordinates
     */
    const double operator()(const double x, const double y) const; /* throws */

		Grid& operator+=(const Grid&);
		Grid& operator-=(const Grid&);
		Grid& operator*=(double c);

  private:
    void readHeader(std::istream& a_Ist); /* throws */
    void readData(std::istream& a_Ist); /* throws */

	private:
		SpaceParams m_Coords;
		double      m_NoData;          // no data value
		Array2D       m_Data;          // values at the grid points
};

// Inline methods
double& Grid::operator()(const unsigned int i, const unsigned int j) const
{
   return m_Data(i, j);
}

inline unsigned int Grid::Nx() const
{
  return m_Coords.Nx;
}

inline unsigned int Grid::Ny() const
{
  return m_Coords.Ny;
}

inline double Grid::Dx()	const
{
  return m_Coords.Dx;
}

inline double Grid::Dy()	const
{
  return m_Coords.Dy;
}

inline double Grid::Xll() const
{
  return m_Coords.Xll;
}

inline double Grid::Yll() const
{
  return m_Coords.Yll;
}

inline double Grid::X(unsigned int i) const
{
  return Xll() + i*Dx();
}

inline double Grid::Y(unsigned int j) const
{
  return Yll() + j*Dy();
}

inline bool Grid::IsData(unsigned int i, unsigned int j) const
{
  return (m_Data(i, j) != m_NoData);
}

inline double Grid::NoData() const
{
  return m_NoData;
}

// Non-member functions
Grid operator+(const Grid&, const Grid&);
Grid operator-(const Grid&, const Grid&);
Grid operator*(const Grid&, double);
Grid operator*(double, const Grid&);
std::ostream& operator<<(std::ostream&, const Grid&);

double Min(const Grid& a_Grid);
double Max(const Grid& a_Grid);

double StaggeredValue(const Grid& a_Grid, unsigned int, unsigned int);
double StaggeredGradNormValue(const Grid& a_Grid, unsigned int, unsigned int);

void Export(const Grid& a_Grid, std::string a_FileName);
void XYZ(const Grid& a_Grid, std::string a_FileName);

#endif /* GRID_H_ */
