#ifndef GRID_H_
#define GRID_H_

#include <memory>
#include <string>
#include <vector>

#include "Utility/Array2D.hpp"
#include "SpaceParams.hpp"

class Grid // TODO: this could be a container, i.e. could have iterators
{
	public: 
		// Constructors / destructors
    Grid(std::size_t Nx = 0, std::size_t Ny = 0, double Dx = 0, double Dy = 0, double Xll = 0, double Yll = 0);
    Grid(std::string a_FileName);
		~Grid();

		// Copy constructor and assignment operator
		Grid(const Grid &);
		Grid& operator=(const Grid &);

		// Getters
    std::size_t Nx() const;
    std::size_t Ny() const;
    double Dx()	const;
    double Dy()	const;
    double Xll() const;
    double Yll() const;
    double  X(std::size_t i) const;
    double  Y(std::size_t j) const;
    bool IsData(std::size_t i, std::size_t j) const;
    double NoData() const;

		// Data handling
    void Refine(double ratio);
    /*
     *  Grid refinement or coarsening with ratio r, i.e. the original Dx is divided by r to make up the new mesh size
     * r > 1 : refinement
     * r < 1 : coarsening
     */
    void Refine(double ratioX, double ratioY);

    double& operator()(std::size_t i, std::size_t j);
    double operator()(std::size_t i, std::size_t j) const;
    double& operator()(double i, double j) = delete;
    double operator()(double i, double j) const = delete;
    /*
     *  Interpolates linearly the value of the grid elevation at position (x, y)
     *  Coordinates x and y must be expressed in global coordinates
     *  (i.e. x = Xll + i*Dx, y = Yll + j*Dy)
     */
    double interpolateLinear(double x, double y) const;

		Grid& operator+=(const Grid&);
		Grid& operator-=(const Grid&);
		Grid& operator*=(double c);

  private:
    void readHeader(std::istream& a_Ist);
    void readData(std::istream& a_Ist);

	private:
		SpaceParams m_Coords;
		double      m_NoData;          // no data value
		Array2D       m_Data;          // values at the grid points
};

// Inline methods
inline double& Grid::operator()(std::size_t i, std::size_t j)
{
  return m_Data(i, j);
}

inline double Grid::operator()(std::size_t i, std::size_t j) const
{
  return m_Data(i, j);
}

inline std::size_t Grid::Nx() const
{
  return m_Coords.Nx;
}

inline std::size_t Grid::Ny() const
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

inline double Grid::X(std::size_t i) const
{
  return Xll() + i*Dx();
}

inline double Grid::Y(std::size_t j) const
{
  return Yll() + j*Dy();
}

inline bool Grid::IsData(std::size_t i, std::size_t j) const
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
std::ostream& operator<<(std::ostream&, Grid&);

double Min(const Grid& a_Grid);
double Max(const Grid& a_Grid);

// return staggered grid value at point (i-1/2, j-1/2)
double StaggeredValue(const Grid& a_Grid, std::size_t, std::size_t);

// compute norm of gradient of grid in the staggered grid
double StaggeredGradNormValue(const Grid& a_Grid, std::size_t, std::size_t);

void Export(const Grid& a_Grid, std::string a_FileName);
void XYZ(const Grid& a_Grid, std::string a_FileName);

#endif /* GRID_H_ */
