#include "Grid.hpp"

#include <iostream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <exception>

#include "Utility/Math.hpp"
#include "Utility/Logger/Logger.hpp"

//============================================================================================================================
Grid::Grid(unsigned int ncols, unsigned int nrows, double dx, double dy, double xl, double yl)
	: m_Coords(ncols, nrows, dx, dy, xl, yl)
	, m_NoData(-9999)
	, m_Data(ncols, nrows)
//============================================================================================================================
{

}

void Grid::readHeader(std::istream& a_Ist)
{
  int bufferSize(512);

  char* line = new char[bufferSize];
  float tmpx, tmpy;
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpx);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpy);

  assert(tmpx != 0); assert(tmpy != 0);

  if (!N_MathUtils::isInteger(tmpx) || !N_MathUtils::isInteger(tmpy)) {
    LOG_ERR("ncols / nrows not integer in grid file");
    LOG_ERR("ncols, nrows = " << tmpx << "\t" << tmpy);
    throw std::runtime_error("ncols / nrows not integer in grid file");
  }

  m_Coords.Nx = (unsigned int) tmpx; m_Coords.Ny = (unsigned int) tmpy;

  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Xll);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Yll);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Dx);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_NoData);
  m_Coords.Dy = m_Coords.Dx;
}

void Grid::readData(std::istream& a_Ist)
{
  m_Data = Array2D(Nx(), Ny());
  for (unsigned int j(Ny()); j--; )
  {
    for (unsigned int i(0); i < Nx(); ++i)
    {
       a_Ist >> m_Data(i, j);
    }
  }
}

//============================================================================================================================
Grid::Grid(std::string a_FileName)
//============================================================================================================================
{
  try
  {
    std::ifstream ist(a_FileName.c_str(), std::ios::in);
    LOG_INF("Opening file " << a_FileName);
    readHeader(ist);
    readData(ist);
    ist.close();
  }
  catch(std::ifstream::failure& e)
  {
    LOG_ERR("Cannot open file " << a_FileName << ": " << e.what());
  }
  catch(std::runtime_error& e)
  {
    LOG_ERR("Corrupt grid file or index out of range: " << e.what());
  }
  catch(...)
  {
    LOG_ERR("Caught unknown exception.");
  }
}

//============================================================================================================================
Grid::~Grid()
//============================================================================================================================
{

}

//============================================================================================================================
Grid::Grid(const Grid & g) // a copy constructor creates a new object from an old one
	: m_Coords(g.m_Coords)
	, m_NoData(g.m_NoData)
	, m_Data(g.m_Data)
//============================================================================================================================
{

}

//============================================================================================================================
Grid& Grid::operator=(const Grid& g) // an assignment operator overwrites an existing object
//============================================================================================================================
{
	m_Coords = g.m_Coords;
	m_NoData = g.m_NoData;
	m_Data = g.m_Data;
	return *this;
}

/*//============================================================================================================================
void Grid::Clear()
//============================================================================================================================
{
	m_Data();
}*/

//============================================================================================================================
const double Grid::operator()(const double x, const double y) const
// Perform linear interpolation to get the surface value at point (x, y)
//============================================================================================================================
{
	std::vector<double> w{ x, y, 0 }; 

	// define lower left corner grid coordinates of w
	unsigned int i = (unsigned int)(w[0] - Xll()) / Dx(), j = (unsigned int)(w[1] - Yll()) / Dy();

	if (j >= Ny() || i >= Nx()) // floor rounding guarantees i <= Nx-1 and j <= Ny-1
	{
    LOG_ERR("Point to be interpolated outside of the grid (i, j) = (" << i << "," << j << ")");
    throw std::range_error("Point to be interpolated outside of the grid");
	}

	// this is to deal with the case where w lies at the top or right boundary of the grid
	unsigned int I(i == Nx() - 1 ? i : i + 1);
	unsigned int J(j == Ny() - 1 ? j : j + 1);

	// define the four nearest neighbours of point w
	std::vector<std::vector<double>> bounds = {
		  std::vector<double> { X(i), Y(j), (*this)(i, j) }
		, std::vector<double> { X(i), Y(J), (*this)(i, J) } 
		, std::vector<double> { X(I), Y(J), (*this)(I, J) } 
		, std::vector<double> { X(I), Y(j), (*this)(I, j) }
	};

  return N_MathUtils::getPlaneElevation(bounds, w);
}

//============================================================================================================================
Grid& Grid::operator+=(const Grid& right)
//============================================================================================================================
{
	assert(m_Coords == right.m_Coords);
	m_Data += right.m_Data;
	return *this;
}

//============================================================================================================================
Grid& Grid::operator-=(const Grid& right)
//============================================================================================================================
{
	assert(m_Coords == right.m_Coords);
	m_Data -= right.m_Data;
	return *this;
}

//============================================================================================================================
Grid& Grid::operator*=(double c)
//============================================================================================================================
{
	m_Data *= c;
	return *this;
}

// Non-member functions

//============================================================================================================================
std::ostream& operator<<(std::ostream& ost, const Grid& g)
//============================================================================================================================
{
	assert(g.Dx() == g.Dy());
	ost << "NCOLS\t"        << g.Nx() << "\n"
			<< "NROWS\t"        << g.Ny() << std::endl;
	ost.precision(10);
	ost << "XLLCORNER\t"    << g.Xll() << "\n"
			<< "YLLCORNER\t"    << g.Yll() << "\n"
			<< "CELLSIZE\t"     << g.Dx()  << "\n"
			<< "NODATA_value\t" << g.NoData() << std::endl;

	ost.precision(4);
	double tmp(0.);
  for (unsigned int j(g.Ny()); j--; )
	{
    for (unsigned int i(0); i < g.Nx(); ++i)
		{
      tmp = g(i, j); assert(!std::isnan(tmp));
			ost << std::fixed << std::setw(10) << tmp << " "; // Forgetting about formatting makes this operation faster
		}
	}

	return ost;
}

//============================================================================================================================
Grid operator+(const Grid& lhs, const Grid& rhs)
//============================================================================================================================
{
	return Grid(lhs) += rhs;
}

//============================================================================================================================
Grid operator-(const Grid& lhs, const Grid& rhs)
//============================================================================================================================
{
	return Grid(lhs) -= rhs;
}

//============================================================================================================================
Grid operator*(const Grid& lhs, double rhs)
//============================================================================================================================
{
	return Grid(lhs) *= rhs;
}

//============================================================================================================================
Grid operator*(double lhs, const Grid& rhs)
//============================================================================================================================
{
	return Grid(rhs) *= lhs;
}

//============================================================================================================================
double Max(const Grid& a_Grid)
//============================================================================================================================
{
	double m(a_Grid(0., 0.)), tmp(0.);
	for (unsigned int k(0); k<a_Grid.Nx(); ++k) {
		for (unsigned int j(0); j<a_Grid.Ny(); ++j) {
			tmp = a_Grid(k, j);
			if (tmp > m) m = tmp;
		}
	}
	return m;
}

//============================================================================================================================
double Min(const Grid& a_Grid)
//============================================================================================================================
{
	double m(a_Grid(0., 0.)), tmp(0.);
	for (unsigned int k(0); k<a_Grid.Nx(); ++k) {
		for (unsigned int j(0); j<a_Grid.Ny(); ++j) {
			tmp = a_Grid(k, j);
			if (tmp < m) m = tmp;
		}
	}
	return m;
}

//============================================================================================================================
double StaggeredValue(const Grid& a_Grid, unsigned int i, unsigned int j) {
// return staggered grid value at point (i-1/2, j-1/2)
//============================================================================================================================
	assert(a_Grid.Dx() == a_Grid.Dy());
	return (a_Grid(i - 1, j - 1) + a_Grid(i, j - 1) + a_Grid(i - 1, j) + a_Grid(i, j)) / 4.;
}

//============================================================================================================================
double StaggeredGradNormValue(const Grid& a_Grid, unsigned int i, unsigned int j) {
// compute norm of gradient of grid in the staggered grid
//============================================================================================================================
	assert(a_Grid.Dx() == a_Grid.Dy());
	return sqrt((a_Grid(i,     j) - a_Grid(i - 1, j - 1))*(a_Grid(i,     j) - a_Grid(i - 1, j - 1))
						+ (a_Grid(i, j - 1) - a_Grid(i - 1,     j))*(a_Grid(i, j - 1) - a_Grid(i - 1,     j))) / (std::sqrt(2)*a_Grid.Dx());
}

//============================================================================================================================
void Export(const Grid& a_Grid, std::string a_FileName) {
//============================================================================================================================
  std::ofstream ofs(a_FileName.c_str());
  ofs << a_Grid;
  ofs.close();
}

//============================================================================================================================
void XYZ(const Grid& a_Grid, std::string a_FileName){
// Export to xyz format
//============================================================================================================================
  try
  {
    std::ofstream ofs(a_FileName.c_str());
    for (unsigned int i(0); i < a_Grid.Nx(); ++i)
    {
      for (unsigned int j(0); j < a_Grid.Ny(); ++j)
      {
        ofs << a_Grid.X(i) << "\t" << a_Grid.Y(j) << "\t" << std::setprecision(4) << a_Grid(i, j) << std::endl;
      }
      ofs << std::endl;
    }
    ofs.close();
  }
  catch(std::ofstream::failure& e)
  {
    LOG_ERR("Cannot write file " << a_FileName << ": " << e.what());
  }
  catch(std::range_error& e)
  {
    LOG_ERR("Index out of range: " << e.what());
  }
  catch(...)
  {
    LOG_ERR("Caught unknown exception.");
  }
}
