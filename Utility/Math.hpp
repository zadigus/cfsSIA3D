#ifndef MATH_H_
#define MATH_H_

#include <cmath>
#include <vector>
#include <functional>

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
  double getPlaneElevation(const std::vector<std::vector<double>>& a_Points, const std::vector<double>& a_ConsideredPoint);


  // Helper classes
  class IsCloserToConsideredPoint : std::binary_function<const std::vector<double>&, const std::vector<double>&, bool>
  {
    public:
      IsCloserToConsideredPoint(const std::vector<double>& a_ConsideredPoint) : m_ConsideredPoint(a_ConsideredPoint) { }
      bool operator()(const std::vector<double>& a_Point1, const std::vector<double>& a_Point2)
      {
        double dist1(N_MathUtils::EuclideanDistance(a_Point1, m_ConsideredPoint, 2));
        double dist2(N_MathUtils::EuclideanDistance(a_Point2, m_ConsideredPoint, 2));
        return dist1 < dist2;
      }

    private:
      std::vector<double> m_ConsideredPoint;
  };
}

#endif
