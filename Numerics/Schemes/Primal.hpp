#ifndef PRIMAL_HPP_
#define PRIMAL_HPP_

#include <memory>

namespace Mathematics {

	class DiffusionAlgorithm;
	class ClimateAlgorithm;
	class ProjectionAlgorithm;

	class Primal
	{
		public:
			Primal();  // TODO: figure out what kind of parameters to feed this class with; set the various algorithms here (read what algo to use from the config)
			~Primal(); 

			// General purpose
			void Run(); 								// compute one whole evolution from time ti to time tf
			void Iterate(int);					// compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
			void Store(); 							// store every velocity and ice thickness iterate

			// Primal algorithm
			void Diffusion();						// solve the diffusion step
			void Climate(); 	        // compute step dh/dt = B
			void Projection();					// enforce H >= 0

		private:
			// TODO: include H?

			// Strategy pattern
			std::unique_ptr<DiffusionAlgorithm>   _DiffusionAlgo;
			std::unique_ptr<ClimateAlgorithm>       _ClimateAlgo;
			std::unique_ptr<ProjectionAlgorithm> _ProjectionAlgo;
	};

}

#endif