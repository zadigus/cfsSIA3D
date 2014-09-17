#ifndef MATH_H_
#define MATH_H_

#include <cmath>
#include <vector>

namespace Math
{

	static double ZERO = 1e-10;

	template <class T> static bool isInteger(T x) 
	{ 
		return std::abs(x-std::floor(x)) ? false : true;  
	}

	double EuclideanDistance(std::vector<double>&, std::vector<double>&, unsigned int=0);
	std::vector<double> crossDiff3D(std::vector<double>&, std::vector<double>&, std::vector<double>&);
	double Heaviside(double);

}

#endif