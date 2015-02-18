#include "Math.hpp"
#include <cassert>
#include <algorithm>

namespace N_MathUtils
{
	//===================================================================================================
  double EuclideanDistance(const std::vector<double> &v1, const std::vector<double> &v2, unsigned int n)
	// Norm of the n first components of v1-v2 
	//===================================================================================================
	{
		assert(v1.size() == v2.size());
		if (!n)
			n = v1.size();
		double d(0);
		for (unsigned int i(0); i < n; ++i)
			d += (v1[i] - v2[i])*(v1[i] - v2[i]);
		return std::sqrt(d);
	}

	//===================================================================================================
  std::vector<double> crossDiff3D(const std::vector<double> &x, const std::vector<double> &y, const std::vector<double> &z)
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

  //===================================================================================================
  double getPlaneElevation(std::vector<std::vector<double>>& a_Points, const std::vector<double>& a_ConsideredPoint)
  //===================================================================================================
  {
    // find the 3 closest vectors to w
    std::sort(  a_Points.begin()
              , a_Points.end()
              , [a_ConsideredPoint] (const std::vector<double>& a_Point1, const std::vector<double>& a_Point2) -> bool
                {
                  return EuclideanDistance(a_Point1, a_ConsideredPoint, 2) < EuclideanDistance(a_Point2, a_ConsideredPoint, 2);
                }
              );

    std::vector<double> n = crossDiff3D(a_Points[0], a_Points[1], a_Points[2]);

    // planar interpolation
    double out = a_Points[0][2];
    if(abs(n[2]) > ZERO)
      out -= (n[0] * (a_ConsideredPoint[0] - a_Points[0][0]) + n[1] * (a_ConsideredPoint[1] - a_Points[0][1])) / n[2];
    assert(!isnan(out));
    return out;
  }

}
