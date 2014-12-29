#ifndef MATHEMATICS_IVECTOR_HPP_
#define MATHEMATICS_IVECTOR_HPP_

#include <memory>

namespace N_Mathematics {

	class IMatrix;

	class IVector
	{
		public:
			IVector();
			virtual ~IVector();

			virtual double& operator[](unsigned int i) = 0;

			virtual int size() = 0;
	};

}

#endif