#ifndef CONSTANTSL_H_
#define CONSTANTSL_H_

#include "SlidingLaw.hpp"

class Grid;

class ConstantSL: public SlidingLaw {
public:
	ConstantSL(std::string, int);
	~ConstantSL();
	void Generate(Grid&, int);
};

#endif
