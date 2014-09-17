#ifndef RHEOLOGYFACTORY_H_
#define RHEOLOGYFACTORY_H_

#include <memory>

class Rheology;
class Component; 

class RheologyFactory
{
public:
	// factory method
	static Rheology* make(Component* aRheology);
};

#endif