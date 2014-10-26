#include "Grid.hpp"

#include <iostream>
#include <cassert>
#include <cstdlib>
#include <iomanip>
#include <limits>

#include "Utility/Math.hpp"

//==============================================================================
Grid::Grid(unsigned int ncols, unsigned int nrows, double dx, double dy, double xl, double yl)
	: m_Coords(ncols, nrows, dx, dy, xl, yl)
	, m_NoData(-9999)
	, m_Data(ncols, nrows)
//==============================================================================
{

}

//==============================================================================
Grid::Grid(std::string fileName)
//==============================================================================
{
	std::ifstream ist(fileName.c_str(), std::ios::in);

	if (ist)
	{
		std::cout << "Opening file " << fileName << std::endl; // TODO: log that in a file
		int bufferSize(512);
		
		// Read grid header
		char* line = new char[bufferSize];	
		float tmpx, tmpy;
		ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpx);
		ist.getline(line, bufferSize); sscanf(line, "%*s %e", &tmpy);

		assert(tmpx != 0); assert(tmpy != 0);

		if (!N_MathUtils::isInteger(tmpx) || !N_MathUtils::isInteger(tmpy)) {
			std::cerr << "ncols / nrows not integer in grid file" << std::endl;
			std::cerr << "ncols, nrows = " << tmpx << "\t" << tmpy << std::endl;
			exit(1);
		}

		m_Coords.Nx = (unsigned int) tmpx; m_Coords.Ny = (unsigned int) tmpy;

		ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Xll);
		ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Yll);
		ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_Coords.Dx);
		ist.getline(line, bufferSize); sscanf(line, "%*s %lf", &m_NoData);
		m_Coords.Dy = m_Coords.Dx;

		m_Data.Reset(Nx(), Ny());

		// Read data
		for (unsigned int j(Ny()); j >= 1; --j) // that trick is used (finish with j = 1 instead of 0) because it doesn't work with 0 with unsigned ints
		{
			for (unsigned int i(1); i <= Nx(); ++i)
			{
				ist >> m_Data(i-1, j-1);
			}
		}

		ist.close();
	}
	else
	{
		std::cerr << "Could not construct grid object because file " << fileName << " does not exist." << std::endl;
		exit(1);
	}
}

//==============================================================================
Grid::~Grid()
//==============================================================================
{
	//std::cout << "Grid::DTOR" << std::endl;
}

//==============================================================================
Grid::Grid(const Grid & g) // a copy constructor creates a new object from an old one
	: m_Coords(g.m_Coords)
	, m_NoData(g.m_NoData)
	, m_Data(g.m_Data)
//==============================================================================
{

}

//==============================================================================
Grid& Grid::operator=(const Grid& g) // an assignment operator overwrites an existing object
//==============================================================================
{
	//assert(g._Coords == _Coords);
	m_Coords = g.m_Coords;
	m_NoData = g.m_NoData;
	m_Data = g.m_Data;
	return *this;
}

//==============================================================================
void Grid::Clear()
//==============================================================================
{
	m_Data();
}

//==============================================================================
std::ostream& operator<<(std::ostream& ost, Grid& g)
//==============================================================================
{
	assert(g.Dx() == g.Dy()); 
	ost << "NCOLS\t"        << g.Nx() << "\n"
		  << "NROWS\t"        << g.Ny() << std::endl;
	ost.precision(10);
	ost << "XLLCORNER\t"    << g.Xll() << "\n"
		  << "YLLCORNER\t"    << g.Yll() << "\n"
		  << "CELLSIZE\t"     << g.Dx()  << "\n"
			<< "NODATA_value\t" << g.m_NoData << std::endl;

	ost.precision(4);
	double tmp(0.);
	for (unsigned int j(g.Ny()); j >= 1; --j) // go from 1 to Ny because -1 is positive when considered as an unsigned int
	{
		for (unsigned int i(1); i <= g.Nx(); ++i)
		{ 
			tmp = g(i, j); assert(!std::isnan(tmp)); 
			ost << std::fixed << std::setw(10) << tmp << " "; // Forgetting about formatting makes this operation faster
		}
	}

	return ost;
}

//============================================================================================================================
const double Grid::operator()(const double x, const double y) 
// Perform linear interpolation to get the surface value at point (x, y)
//============================================================================================================================
{
	std::vector<double> w{ x, y, 0 }; 

	// define lower left corner grid coordinates of w
	unsigned int i = (unsigned int)(w[0] - Xll()) / Dx(), j = (unsigned int)(w[1] - Yll()) / Dy();

	if (j >= Ny() || i >= Nx()) // floor rounding guarantees i <= Nx-1 and j <= Ny-1
	{
		std::cerr << "Point to be interpolated outside the grid (i, j) = (" << i << "," << j << ")" << std::endl;
		exit(1);
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

	// determine the farthest point from w (linear interpolation on a plane requires only 3 vectors)
	double tmp(0), min(std::numeric_limits<double>::max()), max(0), minVal(0);
	std::vector<std::vector<double>>::iterator erase_pos;
	for (std::vector<std::vector<double>>::iterator it = bounds.begin(); it != bounds.end(); ++it)
	{
		tmp = N_MathUtils::EuclideanDistance(*it, w, 2);
		if (tmp > max) // find element with maximal distance to the considered point w
		{
			max = tmp;
			erase_pos = it;
		}

		if (tmp < min) // find the height of the closest vector to w
		{
			min = tmp;
			minVal = (*it)[2];
		}
	}
	bounds.erase(erase_pos);

	// compute normal to the plane spanned by the 3 remaining vectors
	std::vector<double> n = N_MathUtils::crossDiff3D(bounds[0], bounds[1], bounds[2]);

	// planar interpolation
	double out = (abs(n[2]) < N_MathUtils::ZERO) ? minVal : bounds[0][2] - (n[0] * (w[0] - bounds[0][0]) + n[1] * (w[1] - bounds[0][1])) / n[2];
	assert(!isnan(out));
	return out; // return interpolated value
}

//==============================================================================
void Grid::Export(std::string fileName) {
//==============================================================================
	std::ofstream ofs(fileName.c_str());
	ofs << *this;
	ofs.close();
}

//============================================================================================================================
void Grid::XYZ(std::string fileName){
// Export to xyz format
//============================================================================================================================
	std::ofstream ofs(fileName.c_str()); 
	
	if (ofs)
	{
		for (unsigned int i(0); i < Nx(); ++i)
		{
			for (unsigned int j(0); j < Ny(); ++j)
			{
				ofs << X(i) << "\t" << Y(j) << "\t" << std::setprecision(4) << (*this)(i, j) << std::endl;
			}
			ofs << std::endl;
		}
		ofs.close();
	}
	else
	{
		std::cerr << "Cannot write into file " << fileName << std::endl;
		exit(1);
	}
}

//==============================================================================
double Grid::Max() {
//==============================================================================
	double m(m_Data(0, 0)), tmp(0.);
	for (unsigned int k(0); k<Nx(); ++k) {
		for (unsigned int j(0); j<Ny(); ++j) {
			tmp = m_Data(k, j);
			if (tmp > m) m = tmp;
		}
	}
	return m;
}

//==============================================================================
double Grid::Min() {
//==============================================================================
	double m(m_Data(0, 0)), tmp(0.);
	for (unsigned int k(0); k<Nx(); ++k) {
		for (unsigned int j(0); j<Ny(); ++j) {
			tmp = m_Data(k, j);
			if (tmp < m) m = tmp;
		}
	}
	return m;
}

//============================================================================================================================
void Grid::Refine(double rx, double ry) 
// Grid refinement or coarsening with ratio r, i.e. the original Dx is divided by r to make up the new mesh size
// r > 1 : refinement
// r < 1 : coarsening
//============================================================================================================================	
{
	Grid tmp(*this);
	double Xmax(X(Nx())), Ymax(Y(Ny()));
	m_Coords.Dx /= rx;
	m_Coords.Dy /= ry;
	m_Coords.Nx *= rx; 
	m_Coords.Ny *= ry;

	double x(0.0), y(0.0); unsigned int i(0), j(0);
	while (x < Xmax) {
		y = 0.0; j = 0;
		while (y < Ymax) {
			(*this)(i, j) = tmp(x, y);
			y += Dy(); ++j;
		}
		x += Dx(); ++i;
	}
}

//============================================================================================================================
void Grid::Refine(double r)
//============================================================================================================================
{
	Refine(r, r);
}

//=========================================================================================
double Grid::Staggered(unsigned int i, unsigned int j) {
	// return staggered grid value at point (i-1/2, j-1/2)
	//=========================================================================================
	assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < Nx()); assert(j < Ny());
	return ((*this)(i - 1, j - 1) + (*this)(i, j - 1) + (*this)(i - 1, j) + (*this)(i, j)) / 4.;
}

//=========================================================================================
double Grid::StaggeredGradNorm(unsigned int i, unsigned int j) {
	// compute norm of gradient of grid in the staggered grid
	//=========================================================================================
	assert(i - 1 >= 0); assert(j - 1 >= 0); assert(i < Nx()); assert(j < Ny()); assert(Dx() == Dy());
	return sqrt(((*this)(i,     j) - (*this)(i - 1, j - 1))*((*this)(i,     j) - (*this)(i - 1, j - 1))
		        + ((*this)(i, j - 1) - (*this)(i - 1,     j))*((*this)(i, j - 1) - (*this)(i - 1,     j))) / (std::sqrt(2)*Dx());
}

//==============================================================================
Grid& Grid::operator+=(const Grid& right)
//==============================================================================
{
	assert(m_Coords == right.m_Coords);
	m_Data += right.m_Data;
	return *this;
}

//==============================================================================
Grid& Grid::operator-=(const Grid& right)
//==============================================================================
{
	assert(m_Coords == right.m_Coords);
	m_Data -= right.m_Data;
	return *this;
}

//==============================================================================
Grid& Grid::operator*=(double c)
//==============================================================================
{
	m_Data *= c;
	return *this;
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

/*//==============================================================================
Grid operator+(Grid& left, Grid& right)
//==============================================================================
{
	assert(left._Coords == right._Coords);
	Grid out(left);
	out += right;
	return out; // TODO: this could be: Grid(left) += right
	return Grid(left) += right;
}

//==============================================================================
Grid operator-(Grid& left, Grid& right)
//==============================================================================
{
	assert(left._Coords == right._Coords);

	Grid out(left);
	out -= right;

	return out;
	return Grid(left) -= right;
}


//==============================================================================
Grid Grid::operator*(const double c)
//==============================================================================
{
	Grid out(*this);
	out *= c;
	return out;
	return Grid(*this) *= c;
}*/