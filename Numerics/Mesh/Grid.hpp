#ifndef GRID_H_
#define GRID_H_

#include <memory>
#include <string>
#include <fstream>
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

		//void Set(double dx) { _Coords.Dx = dx; }


		// Getters
		unsigned int Nx() const		{ return _Coords.Nx; }
		unsigned int Ny() const		{ return _Coords.Ny; }
		double Dx()	const 				{ return _Coords.Dx; }
		double Dy()	const 				{ return _Coords.Dy; }
		double Xll() const 				{ return _Coords.Xll; }
		double Yll() const				{ return _Coords.Yll; }
		double  X(unsigned int i) const		{ return Xll() + i*Dx(); } // Local coordinates
		double  Y(unsigned int j) const		{ return Yll() + j*Dy(); }
		bool IsData(unsigned int i, unsigned int j) { return (_Data(i, j) != _NoData); }

		// Data handling
		void Clear();
		void Refine(double);
		void Refine(double, double);

		double& operator()(const unsigned int i, const unsigned int j) { return _Data(i, j); }
		const double operator()(const double x, const double y);

		Grid& operator+=(Grid&);
		Grid& operator-=(Grid&);
		Grid& operator*=(double c);
		Grid operator*(const double c);

		friend Grid operator+(Grid&, Grid&); // TODO: see Scott Meyers, this doesn't need to be a friend operation
		friend Grid operator-(Grid&, Grid&);

		friend std::ostream& operator<<(std::ostream&, Grid&);

		// Staggered grid
		double Staggered(unsigned int, unsigned int);
		double StaggeredGradNorm(unsigned int, unsigned int);

		// Export
		void Export(std::string);
		void XYZ(std::string);

		// Grid properties
		double Min();
		double Max();

	private:
		SpaceParams _Coords;
		double      _NoData;          // no data value
		Array2D       _Data;          // values at the grid points
};

#endif /* GRID_H_ */
