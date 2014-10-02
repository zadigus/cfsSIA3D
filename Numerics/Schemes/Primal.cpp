#include "Primal.hpp"

// TODO: define these algos
#include "DiffusionAlgo.hpp"
#include "ClimateAlgo.hpp"
#include "ProjectionAlgo.hpp"

namespace Mathematics {

	Primal::Primal() // TODO: define what config to feed that ctor with
	{

	}

	void Primal::Diffusion()
	{
		_DiffusionAlgo->Run(); // TODO: that should update the ice thickness
	}

	void Primal::Climate()
	{
		_ClimateAlgo->Run();
	}

	void Primal::Projection()
	{
		_ProjectionAlgo->Run();
	}

}