#ifndef GLACIERCOMPONENT_H_
#define GLACIERCOMPONENT_H_

#include "ModelComponent/ModelComponent.hpp"

#include <memory>
#include <string>
#include <map>


namespace N_Configuration {
	class Component;
}

namespace N_Glacier {

	// Interface class for a general physical component
	class GlacierComponent : public ModelComponent 
	{ 
		public:
			GlacierComponent(const N_Configuration::Component& aComponent);
			GlacierComponent();
			virtual ~GlacierComponent();
	};
}

#endif /* GLACIERCOMPONENT_H_ */
