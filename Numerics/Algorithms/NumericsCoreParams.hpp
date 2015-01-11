#ifndef NUMERICSCOREPARAMS_H_
#define NUMERICSCOREPARAMS_H_

#include "Utility/ICoreParams.hpp"

namespace N_Mathematics {

	struct NumericsCoreParams : public ICoreParams
	{
		NumericsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aNumericsCoreConf);
		virtual ~NumericsCoreParams();

		double dt() const;     // time step [a]
		double ti() const;     // initial time [a]
		double tf() const;     // final time [a]
	};

}

#endif