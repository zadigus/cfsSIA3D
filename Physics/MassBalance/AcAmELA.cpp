#include "AcAmELA.hpp"
#include "Utility/Math.hpp"
#include "PhysicsConfiguration.hpp"

AcAmELA::AcAmELA(Component* aComponent) : MassBalance(aComponent)
{
	//_x.resize(4);
	//ReadModelParameters(mbFile, _x, 4);
}

AcAmELA::~AcAmELA() //TODO: double-check that this calls the MassBalance::~MassBalance ...
{ 

}

const double AcAmELA::operator()(const double x, const double y, const double b, const double H)
{
	// only depends on surface altitude
	return (*this)(b, H, H);
}

const double AcAmELA::operator()(const double b, const double H3, const double H2) 
{
	return water2ice(Math::Heaviside(H2) * (am()/2.*(b+H3-ELA())+ac()/2.-sqrt((am()/2.*(b+H3-ELA())-ac()/2.)*(am()/2.*(b+H3-ELA())-ac()/2.)+eps())));
}

double AcAmELA::dB(double b, double H3, double H2) 
{ 
	double tmp(am()/2.*(am()/2.*(b+H3-ELA())-ac()/2.));
	if(tmp != 0.0)
		return water2ice(Math::Heaviside(H2) * (am()/2. - tmp/sqrt((am()/2.*(b+H3-ELA())-ac()/2.)*(am()/2.*(b+H3-ELA())-ac()/2.)+eps())));
	return water2ice(Math::Heaviside(H2) * am()/2.);
}
