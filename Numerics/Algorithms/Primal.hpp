#ifndef PRIMAL_HPP_
#define PRIMAL_HPP_

#include <memory>

#include "Utility/Singleton.hpp"

namespace N_Configuration {
	class ModelConfiguration;
	class ModelCoreConfiguration;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	class NumericsCoreParams;

	class Primal : public Singleton<Primal>
	{
		friend class Singleton<Primal>;

		public:
			void init(std::unique_ptr<N_Configuration::ModelConfiguration>& aMathConf, const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aNumCoreConf);

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

			void Iterate();							// compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
		
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