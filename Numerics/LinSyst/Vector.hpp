#ifndef MATHEMATICS_VECTOR_HPP_
#define MATHEMATICS_VECTOR_HPP_

#include <vector>
#include <memory>

class Grid;

namespace N_Mathematics {

	class Vector
	{
		public:
			Vector(unsigned int MS);
			virtual ~Vector();

			double operator[](unsigned int i) const;

			unsigned int MS();
			void InsertValue(double val);
			void Clear();

			//void toGrid(std::shared_ptr<Grid>& aGrid);

		protected:
			unsigned int m_MS;
			std::vector<double> m_Values;
	};

	inline unsigned int Vector::MS()
	{
		return m_MS;
	}

	inline void Vector::InsertValue(double val)
	{
		m_Values.push_back(val);
	}

	inline double Vector::operator[](unsigned int i) const
	{
		return m_Values.at(i);
	}

}

#endif