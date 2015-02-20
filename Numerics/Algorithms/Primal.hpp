#ifndef PRIMAL_HPP_
#define PRIMAL_HPP_

#include <memory>

#include "Utility/Singleton.hpp"

namespace N_Configuration {
	class ModelConfiguration;
	class ModelCoreConfiguration;
	class Component;
}

namespace N_Mathematics {

	class PrimalAlgorithm;
	class NumericsCoreParams;

	class Primal : public Singleton<Primal>
	{
		friend class Singleton<Primal>;

		public:
      void init(std::unique_ptr<N_Configuration::ModelConfiguration> aMathConf, std::unique_ptr<N_Configuration::ModelCoreConfiguration> aNumCoreConf);

			// General purpose
			void run(); 								// compute one whole evolution from time ti to time tf
      void store(); 							// store every velocity and ice thickness iterate

		private:
			// Ctor/Dtor
			Primal(); 
			~Primal();

			// Configuration setup
			void setComponent(const N_Configuration::Component& aComp, const NumericsCoreParams& aCore);

			// Primal algorithm
      void iterate();							// compute one whole forward iteration consisting of diffusion, accumulation/ablation, projection
      void doDiffusion();					// solve the diffusion step
      void doClimate(); 					// compute step dh/dt = B
      void doProjection();				// enforce H >= 0
		
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
