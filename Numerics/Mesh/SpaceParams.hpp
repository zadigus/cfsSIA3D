#ifndef SPACEPARAMS_H_
#define SPACEPARAMS_H_

struct SpaceParams
{
	SpaceParams(unsigned int = 0, unsigned int = 0, double = 0, double = 0, double = 0, double = 0);
	SpaceParams(const SpaceParams &);
	bool operator==(const SpaceParams& right) const;

	unsigned int Nx;	// number of points along the x direction
	unsigned int Ny;  // number of points along the y direction
	double Dx;				// increment in the x direction
	double Dy;				// increment in the y direction
	double Xll;				// lower left corner's real coordinates
	double Yll;
};

#endif