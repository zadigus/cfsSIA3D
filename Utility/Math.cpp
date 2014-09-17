#include "Math.hpp"
#include <cassert>

namespace Math
{
	//===================================================================================================
	double EuclideanDistance(std::vector<double>& v1, std::vector<double>& v2, unsigned int n)
	// Norm of the n first components of v1-v2 
	//===================================================================================================
	{
		assert(v1.size() == v2.size());
		if (!n)
			n = v1.size();
		double d(0);
		for (unsigned int i(0); i < n; i++)
			d += (v1[i] - v2[i])*(v1[i] - v2[i]);
		return std::sqrt(d);
	}

	//===================================================================================================
	std::vector<double> crossDiff3D(std::vector<double>& x, std::vector<double>& y, std::vector<double>& z)
	// Compute (y-x) cross (z-x)
	//===================================================================================================
	{
		std::vector<double> n = {
				(y[1] - x[1]) * (z[2] - x[2]) - (y[2] - x[2]) * (z[1] - x[1])
			, (y[2] - x[2]) * (z[0] - x[0]) - (y[0] - x[0]) * (z[2] - x[2])
			, (y[0] - x[0]) * (z[1] - x[1]) - (y[1] - x[1]) * (z[0] - x[0])
		};
		return n;
	}

	//===================================================================================================
	double Heaviside(double x)
	//===================================================================================================
	{ 
		return (x > ZERO ? 1.0 : 0.0); 
	}
}