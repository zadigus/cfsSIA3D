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
			unsigned int _MS;
			std::vector<double> _Values;
	};

	inline unsigned int Vector::MS()
	{
		return _MS;
	}

	inline void Vector::InsertValue(double val)
	{
		_Values.push_back(val);
	}

}

#endif