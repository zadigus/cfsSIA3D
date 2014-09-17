#include "GradELA.hpp"
#include "Utility/Math.hpp"
#include "PhysicsConfiguration.hpp"

GradELA::GradELA(Component* aComponent) : MassBalance(aComponent)
{
	//_x.resize(4);
	//ReadModelParameters(mbFile, _x, 4);
}

GradELA::~GradELA() 
{ 

}

const double GradELA::operator()(const double x, const double y, const double b, const double H)
{
	// Only depends on b and H
	return (*this)(b, H, H);
}

const double GradELA::operator()(const double b, const double H3, const double H2) 
{ // = B(b, H3, H2)
	return water2ice(Math::Heaviside(H2) * ((m1()+m2())/2.*(b+H3-ELA())-sqrt(((m1()-m2())/2.*(b+H3-ELA()))*((m1()-m2())/2.*(b+H3-ELA()))+eps())));
}

double GradELA::dB(double b, double H3, double H2) 
{ // dB/ds, especially useful in routine Climate(), because of the Newton process used for it
	double tmp((m1()-m2())*(m1()-m2())/4.*(b+H3-ELA()));
	if(tmp != 0.0)
		return water2ice(Math::Heaviside(H2) * ((m1()+m2())/2. - tmp/sqrt(((m1()-m2())/2.*(b+H3-ELA()))*((m1()-m2())/2.*(b+H3-ELA()))+eps())));
	return water2ice(Math::Heaviside(H2) * (m1()+m2())/2.);
}
