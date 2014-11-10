#ifndef PRIMAL_HPP_
#define PRIMAL_HPP_

#include <memory>

namespace N_Configuration {
	class ModelConfiguration;
}

//namespace N_Glacier {
//	class Glacier;
//}

namespace N_Mathematics {

	class PrimalAlgorithm;
	class NumericsCoreParams;

	class Primal
	{
		public:
			static Primal& getInstance(); 
			void init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf, const std::unique_ptr<NumericsCoreParams>& aNumCoreParams); // , std::shared_ptr<N_Glacier::Glacier>& aGlacier);

			// General purpose
			void Run(); 								// compute one whole evolution from time ti to time tf
			void Store(); 							// store every velocity and ice thickness iterate

		private:
			// Ctor/Dtor
			Primal(); 
			~Primal();

			// Primal algorithm
			void Diffusion();						// solve the diffusion step
			void Climate(); 						// compute step dh/dt = B
			void Projection();					// enforce H >= 0

			void Iterate(); // int l);					// compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
		
		private:
			// Strategy pattern
			std::unique_ptr<PrimalAlgorithm>     m_DiffusionAlgo;
			std::unique_ptr<PrimalAlgorithm>       m_ClimateAlgo;
			std::unique_ptr<PrimalAlgorithm>    m_ProjectionAlgo;

			// Time parameters
			double m_dt; // time step
			double m_ti; // initial time
			double m_tf; // final time
			
	};

}

#endif