#include "SpaceParams.hpp"

SpaceParams::SpaceParams(std::size_t nx, std::size_t ny, double dx, double dy, double xll, double yll)
	: Nx(nx) 
	, Ny(ny)
	, Dx(dx)
	, Dy(dy)
	, Xll(xll)
	, Yll(yll) 
{ 

}

SpaceParams::SpaceParams(const SpaceParams & right) 
	: Nx(right.Nx)
	, Ny(right.Ny)
	, Dx(right.Dx)
	, Dy(right.Dy)
	, Xll(right.Xll)
	, Yll(right.Yll) 
{ 

}

bool SpaceParams::operator==(const SpaceParams& right) const
{
	return Nx == right.Nx &&
		Ny == right.Ny &&
		Dx == right.Dx &&
		Dy == right.Dy &&
		Xll == right.Xll &&
		Yll == right.Yll;
}
