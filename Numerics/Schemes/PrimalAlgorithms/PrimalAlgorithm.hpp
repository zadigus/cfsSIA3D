#ifndef PRIMALALGORITHM_HPP_
#define PRIMALALGORITHM_HPP_

#include <memory>

class Grid;

namespace N_Mathematics {

	class PrimalAlgorithm
	{
		public:
			PrimalAlgorithm(const std::shared_ptr<Grid>& H);
			virtual ~PrimalAlgorithm();
			virtual void Run() = 0; 

		protected:
			std::shared_ptr<Grid> _H;
	};

}

#endif