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
			PrimalAlgorithm(const N_Configuration::Component& aComponent);
			PrimalAlgorithm();
			virtual ~PrimalAlgorithm();

      virtual void transform(N_Glacier::Glacier& a_Glacier) = 0;
      
//		protected:
//			N_Glacier::Glacier& m_glacier;
	};

}

#endif
