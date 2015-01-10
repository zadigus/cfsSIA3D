#ifndef NUMERICSCOREPARAMS_H_
#define NUMERICSCOREPARAMS_H_

#include <memory>
#include <map>
#include <string>

namespace N_Configuration {
	class ModelCoreConfiguration;
}

namespace N_Mathematics {

	struct NumericsCoreParams
	{
		NumericsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aNumericsCoreConf);

		double dt() const;     // time step [a]
		double ti() const;     // initial time [a]
		double tf() const;     // final time [a]

		std::map<std::string, std::string> m_parameters;
	};

}

#endif