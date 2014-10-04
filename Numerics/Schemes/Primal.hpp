#ifndef PRIMAL_HPP_
#define PRIMAL_HPP_

#include <memory>

namespace N_Configuration {
	class ModelConfiguration;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	//class ClimateAlgorithm;
	//class ProjectionAlgorithm;

	class Primal
	{
		public:
			static Primal& getInstance();
			void init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf);

			// General purpose
			void Run(); 								// compute one whole evolution from time ti to time tf
			void Iterate(int);					// compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
			void Store(); 							// store every velocity and ice thickness iterate

			// Primal algorithm
			void Diffusion();						// solve the diffusion step
			void Climate(); 						// compute step dh/dt = B
			void Projection();					// enforce H >= 0

		private:
			Primal(); 
			~Primal();
			// TODO: include H? No, include Glacier

			// Strategy pattern
			std::unique_ptr<PrimalAlgorithm>     _DiffusionAlgo;
			std::unique_ptr<PrimalAlgorithm>       _ClimateAlgo;
			std::unique_ptr<PrimalAlgorithm>    _ProjectionAlgo;
	};

}

#endif