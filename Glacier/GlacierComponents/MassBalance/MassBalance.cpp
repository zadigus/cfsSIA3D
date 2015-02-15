#include "MassBalance.hpp"

#include "Configuration/ModelConfiguration.hpp"
#include "PhysicsCoreParams.hpp"

namespace N_Glacier {

	MassBalance::MassBalance(const PhysicsCoreParams& a_PhysCoreParams, const N_Configuration::Component& a_Component)
		: GlacierComponent(a_Component)
		, m_rho_ice(a_PhysCoreParams.rho_i())
		, m_rho_water(a_PhysCoreParams.rho_w())
	{

	}

	MassBalance::MassBalance(const PhysicsCoreParams& a_PhysCoreParams)
		: GlacierComponent()
		, m_rho_ice(a_PhysCoreParams.rho_i())
		, m_rho_water(a_PhysCoreParams.rho_w())
	{

	}

	MassBalance::~MassBalance()
	{

	}

}

/*void MassBalance::Export(Grid & b, Grid & H, string fileName) {
	int nx(b.get_nx()), ny(b.get_ny()); double dx(b.get_deltax());
	Grid B(nx, ny, dx);
	for (int i = 0; i<nx; ++i)
	for (int j = 0; j<ny; ++j)
		B(i, j) = operator()(b(i, j), H(i, j), H(i, j)); // not exactly B, but approximately this is true
	B.Export(fileName);
	B.Delete();
}*/
