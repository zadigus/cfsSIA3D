#ifndef SPACEPARAMS_H_
#define SPACEPARAMS_H_

#include <cstddef>

struct SpaceParams
{
  SpaceParams(std::size_t = std::size_t(0), std::size_t = std::size_t(0), double = 0, double = 0, double = 0, double = 0);
	SpaceParams(const SpaceParams &);
	bool operator==(const SpaceParams& right) const;

  std::size_t Nx;   // number of points along the x direction
  std::size_t Ny;   // number of points along the y direction
	double Dx;				// increment in the x direction
	double Dy;				// increment in the y direction
	double Xll;				// lower left corner's real coordinates
	double Yll;
};

#endif
