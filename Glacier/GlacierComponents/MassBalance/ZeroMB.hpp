#ifndef ZEROMB_H_
#define ZEROMB_H_

#include "GradELA.hpp"

class Grid;

namespace N_Glacier {

	class ZeroMB : public GradELA {
	public:
		// Constructor / destructor
		ZeroMB();
		virtual ~ZeroMB();
	};

}

#endif