#ifndef MATH_H_
#define MATH_H_

#include <cmath>
#include <vector>
//#include <functional>

namespace N_MathUtils
{

	static double ZERO = 1e-10;

	template <class T> static bool isInteger(T x) 
	{ 
		return std::abs(x-std::floor(x)) ? false : true;  
	}

  double EuclideanDistance(const std::vector<double>&, const std::vector<double>&, unsigned int=0);
  std::vector<double> crossDiff3D(const std::vector<double>&, const std::vector<double>&, const std::vector<double>&);
	double Heaviside(double);
  double getPlaneElevation(std::vector<std::vector<double>>& a_Points, const std::vector<double> &a_ConsideredPoint);
}

#endif
