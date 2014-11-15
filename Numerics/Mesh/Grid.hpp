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
		unsigned int Nx() const		{ return m_Coords.Nx; }
		unsigned int Ny() const		{ return m_Coords.Ny; }
		double Dx()	const 				{ return m_Coords.Dx; }
		double Dy()	const 				{ return m_Coords.Dy; }
		double Xll() const 				{ return m_Coords.Xll; }
		double Yll() const				{ return m_Coords.Yll; }
		double  X(unsigned int i) const		{ return Xll() + i*Dx(); } // Local coordinates
		double  Y(unsigned int j) const		{ return Yll() + j*Dy(); }
		bool IsData(unsigned int i, unsigned int j) { return (m_Data(i, j) != m_NoData); }

		// Data handling
		//void Clear();
		void Refine(double ratio);
		void Refine(double ratioX, double ratioY);

		double& operator()(const unsigned int i, const unsigned int j) { return m_Data(i, j); }
		const double operator()(const double x, const double y);

		Grid& operator+=(const Grid&);
		Grid& operator-=(const Grid&);
		Grid& operator*=(double c);
		//Grid operator*(const double c);

		//friend Grid operator+(Grid&, Grid&); 
		//friend Grid operator-(Grid&, Grid&);

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
		SpaceParams m_Coords;
		double      m_NoData;          // no data value
		Array2D       m_Data;          // values at the grid points
};

Grid operator+(const Grid&, const Grid&);
Grid operator-(const Grid&, const Grid&);
Grid operator*(const Grid&, double);
Grid operator*(double, const Grid&);

#endif /* GRID_H_ */
