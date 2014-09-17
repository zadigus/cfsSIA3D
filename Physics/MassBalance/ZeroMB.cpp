#include "ZeroMB.hpp"
#include "Mesh/Grid.hpp"

ZeroMB::ZeroMB(Component* aComponent) : GradELA(aComponent)
{
 // assert that aComponent doesn't contain anything!
	_parameters.emplace("m1", 0);
	_parameters.emplace("m2", 0);
	_paramters.emplace("ELA", 0);
	_parameters.emplace("eps", 0);
}

ZeroMB::~ZeroMB() 
{ 

}
