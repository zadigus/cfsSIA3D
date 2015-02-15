#ifndef CONSTANTSL_H_
#define CONSTANTSL_H_

#include "SlidingLaw.hpp"

namespace N_Glacier {

	class ConstantSL : public SlidingLaw {
		public:
			ConstantSL(const N_Configuration::Component& a_Component);
			~ConstantSL();

		protected:
			virtual void Init(const std::shared_ptr<Geometry>& a_Geometry);
			virtual void Fill(const std::shared_ptr<Geometry>& a_Geometry, double a_GlenExp);
	};
}

#endif
