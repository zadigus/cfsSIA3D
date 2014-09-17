#include "MassBalance.hpp"
#include "PhysicsConfiguration.hpp"

MassBalance::MassBalance(Component* aComponent)
: PhysicalComponent(aComponent)
, _rho(910) // TODO: this must be hold by the CORE config file for physics
{  

}

MassBalance::~MassBalance()
{

}

/*void MassBalance::Export(Grid & b, Grid & H, string fileName) {
	int nx(b.get_nx()), ny(b.get_ny()); double dx(b.get_deltax());
	Grid B(nx, ny, dx);
	for (int i = 0; i<nx; i++)
	for (int j = 0; j<ny; j++)
		B(i, j) = operator()(b(i, j), H(i, j), H(i, j)); // not exactly B, but approximately this is true
	B.Export(fileName);
	B.Delete();
}*/