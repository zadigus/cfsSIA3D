#include "Grid.hpp"

#include <fstream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <limits>
#include <exception>
#include <algorithm>
#include <functional>

#include "Utility/Math.hpp"
#include "Utility/Logger/Logger.hpp"

using namespace std;
using namespace std::placeholders;

Grid::Grid(size_t ncols, size_t nrows, double dx, double dy, double xl, double yl)
	: m_Coords(ncols, nrows, dx, dy, xl, yl)
	, m_NoData(-9999)
  , m_Data(ncols*nrows, 0)
{

}

void Grid::readHeader(istream& a_Ist)
{
  int bufferSize(512);

  char* line = new char[bufferSize];
  float tmpx, tmpy;
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpx);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpy);

  assert(tmpx != 0 && "Nx = 0"); assert(tmpy != 0 && "Ny = 0");
  assert((N_MathUtils::isInteger(tmpx) && N_MathUtils::isInteger(tmpy)) && "ncols / nrows not integer in grid file");

  m_Coords.Nx = static_cast<size_t>(tmpx);
  m_Coords.Ny = static_cast<size_t>(tmpy);

  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Xll);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Yll);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Dx);
  a_Ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_NoData);
  m_Coords.Dy = m_Coords.Dx;
}

void Grid::readData(istream& a_Ist)
{
  m_Data.resize(Nx()*Ny(), 0);
  for (size_t j(Ny()); j--; )
  {
    for (size_t i(0); i < Nx(); ++i)
    {
      a_Ist >> (*this)(i, j);
    }
  }
}

Grid::Grid(string a_FileName)
{
  try
  {
    ifstream ist(a_FileName.c_str(), ios::in);
    LOG_INF("Opening file " << a_FileName);
    readHeader(ist);
    readData(ist);
    ist.close();
  }
  catch(ifstream::failure& e)
  {
    LOG_ERR("Cannot open file " << a_FileName << ": " << e.what());
    exit(EXIT_FAILURE); // TODO: find a workaround
  }
  catch(...)
  {
    LOG_ERR("Caught unknown exception.");
    exit(EXIT_FAILURE); // TODO: find a workaround
  }
}

Grid::~Grid()
{

}

Grid::Grid(const Grid & g) // a copy constructor creates a new object from an old one
	: m_Coords(g.m_Coords)
	, m_NoData(g.m_NoData)
	, m_Data(g.m_Data)
{

}

Grid& Grid::operator=(const Grid& g) // an assignment operator overwrites an existing object
{
	m_Coords = g.m_Coords;
	m_NoData = g.m_NoData;
	m_Data = g.m_Data;
	return *this;
}

double Grid::max()
{
  return *max_element(m_Data.begin(), m_Data.end());
}

double Grid::min()
{
  return *min_element(m_Data.begin(), m_Data.end());
}

void Grid::resize(double a_rx, double a_ry)
{
  m_Coords.Dx /= a_rx;
  m_Coords.Dy /= a_ry;
  m_Coords.Nx *= a_rx; // this obviously truncates the data
  m_Coords.Ny *= a_ry;
  m_Data.resize(Nx()*Ny());
}

void Grid::refine(double a_rx, double a_ry)
{
  Grid tmp(*this);
  double Xmax(X(Nx())), Ymax(Y(Ny()));

  resize(a_rx, a_ry);

  double x(0.0), y(0.0); size_t i(0), j(0);
  while (x < Xmax) {
    y = 0.0; j = 0;
    while (y < Ymax) {
      (*this)(i, j) = tmp.interpolateLinear(x, y);
      y += Dy(); ++j;
    }
    x += Dx(); ++i;
  }
}

void Grid::refine(double a_r)
{
  refine(a_r, a_r);
}

double Grid::interpolateLinear(double x, double y) const
{
  vector<double> w{ x, y, 0 };

	// define lower left corner grid coordinates of w
  const size_t i = static_cast<size_t>((w[0] - Xll()) / Dx());
  const size_t j = static_cast<size_t>((w[1] - Yll()) / Dy());

  assert((j<Ny() || i<Nx()) && "The point to be interpolated lies outside of the grid");

	// this is to deal with the case where w lies at the top or right boundary of the grid
  const size_t I(i == Nx() - 1 ? i : i + 1);
  const size_t J(j == Ny() - 1 ? j : j + 1);

	// define the four nearest neighbours of point w
  vector<vector<double>> bounds = {
      std::vector<double> { X(i), Y(j), (*this)(i, j) }
    , std::vector<double> { X(i), Y(J), (*this)(i, J) }
    , std::vector<double> { X(I), Y(J), (*this)(I, J) }
    , std::vector<double> { X(I), Y(j), (*this)(I, j) }
	};

  return N_MathUtils::getPlaneElevation(bounds, w);
}

Grid& Grid::operator+=(const Grid& right)
{
	assert(m_Coords == right.m_Coords);
  transform(m_Data.begin(), m_Data.end(), right.m_Data.begin(), m_Data.begin(), plus<double>());
	return *this;
}

Grid& Grid::operator-=(const Grid& right)
{
	assert(m_Coords == right.m_Coords);
  transform(m_Data.begin(), m_Data.end(), right.m_Data.begin(), m_Data.begin(), minus<double>());
	return *this;
}

Grid& Grid::operator*=(double c)
{
  transform(m_Data.begin(), m_Data.end(), m_Data.begin(), bind(multiplies<double>(), _1, c));
	return *this;
}

/*
 * Non-member functions
 */

ostream& operator<<(ostream& ost, const Grid& g)
{
	assert(g.Dx() == g.Dy());
	ost << "NCOLS\t"        << g.Nx() << "\n"
      << "NROWS\t"        << g.Ny() << endl;
	ost.precision(10);
	ost << "XLLCORNER\t"    << g.Xll() << "\n"
			<< "YLLCORNER\t"    << g.Yll() << "\n"
			<< "CELLSIZE\t"     << g.Dx()  << "\n"
      << "NODATA_value\t" << g.noData() << endl;

	ost.precision(4);
	double tmp(0.);
  for (size_t j(g.Ny()); j--; )
	{
    for (size_t i(0); i < g.Nx(); ++i)
		{
      tmp = g(i, j); assert(!std::isnan(tmp));
      ost << fixed << setw(10) << tmp << " "; // Forgetting about formatting makes this operation faster
		}
	}

	return ost;
}

Grid operator+(const Grid& lhs, const Grid& rhs)
{
	return Grid(lhs) += rhs;
}

Grid operator-(const Grid& lhs, const Grid& rhs)
{
	return Grid(lhs) -= rhs;
}

Grid operator*(const Grid& lhs, double rhs)
{
	return Grid(lhs) *= rhs;
}

Grid operator*(double lhs, const Grid& rhs)
{
	return Grid(rhs) *= lhs;
}

double StaggeredValue(const Grid& a_Grid, size_t i, size_t j)
{
	assert(a_Grid.Dx() == a_Grid.Dy());
	return (a_Grid(i - 1, j - 1) + a_Grid(i, j - 1) + a_Grid(i - 1, j) + a_Grid(i, j)) / 4.;
}

double StaggeredGradNormValue(const Grid& a_Grid, size_t i, size_t j)
{
	assert(a_Grid.Dx() == a_Grid.Dy());
	return sqrt((a_Grid(i,     j) - a_Grid(i - 1, j - 1))*(a_Grid(i,     j) - a_Grid(i - 1, j - 1))
            + (a_Grid(i, j - 1) - a_Grid(i - 1,     j))*(a_Grid(i, j - 1) - a_Grid(i - 1,     j))) / (sqrt(2)*a_Grid.Dx());
}

void toGrid(const Grid& a_Grid, string a_FileName)
{
  ofstream ofs(a_FileName.c_str());
  ofs << a_Grid;
  ofs.close();
}

void toXYZ(const Grid& a_Grid, string a_FileName)
{
  try
  {
    ofstream ofs(a_FileName.c_str());
    for (size_t i(0); i < a_Grid.Nx(); ++i)
    {
      for (size_t j(0); j < a_Grid.Ny(); ++j)
      {
        ofs << a_Grid.X(i) << "\t" << a_Grid.Y(j) << "\t" << setprecision(4) << a_Grid(i, j) << endl;
      }
      ofs << endl;
    }
    ofs.close();
  }
  catch(ofstream::failure& e)
  {
    LOG_ERR("Cannot write file " << a_FileName << ": " << e.what());
    exit(EXIT_FAILURE); // TODO: find a workaround
  }
  catch(range_error& e)
  {
    LOG_ERR("Index out of range: " << e.what());
    exit(EXIT_FAILURE);
  }
  catch(...)
  {
    LOG_ERR("Caught unknown exception.");
    exit(EXIT_FAILURE);
  }
}
