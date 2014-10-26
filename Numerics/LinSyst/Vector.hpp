#ifndef MATHEMATICS_VECTOR_HPP_
#define MATHEMATICS_VECTOR_HPP_

#include <vector>

namespace N_Mathematics {

	class Vector
	{
		public:
			Vector(unsigned int MS);
			virtual ~Vector();

			unsigned int MS();
			void InsertValue(double val);
			void Clear();

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

}

#endif