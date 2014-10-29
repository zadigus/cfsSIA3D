#ifndef PRIMALALGORITHM_HPP_
#define PRIMALALGORITHM_HPP_

#include "ModelComponent/ModelComponent.hpp"

#include <memory>
#include <map>

namespace N_Configuration {
	class Component;
}

namespace N_Glacier {
	class Glacier;
}

namespace N_Mathematics {

	// TODO: every output to the console (or the GUI) should be performed by means of the Observer Pattern

	// Interface class for a general numerics component
	class PrimalAlgorithm : public ModelComponent
	{
		public:
			PrimalAlgorithm(N_Configuration::Component* aComponent);
			virtual ~PrimalAlgorithm();

			virtual void Run() = 0; 
      
		protected:
			std::shared_ptr<N_Glacier::Glacier> m_glacier;
	};

}

#endif