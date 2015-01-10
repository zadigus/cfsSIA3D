#include "NumericsCoreParams.hpp"
#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

namespace N_Mathematics {

	NumericsCoreParams::NumericsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aNumericsCoreConf)
	{
		if (!aNumericsCoreConf)
		{
			LOG_ERR("Numerics core parameters not specified.");
			exit(EXIT_FAILURE);
		}

		N_Configuration::ModelCoreConfiguration::Parameter_sequence paramSeq = aNumericsCoreConf->Parameter();
		for (N_Configuration::ModelCoreConfiguration::Parameter_const_iterator it = paramSeq.begin(); it != paramSeq.end(); ++it)
		{
			m_parameters.emplace(it->name(), (*it));
		}
	}

	double NumericsCoreParams::dt() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("dt"));
		return it != m_parameters.end() ? std::stod(it->second) : 0.001;
	}

	double NumericsCoreParams::ti() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("ti"));
		return it != m_parameters.end() ? std::stod(it->second) : 0;
	}

	double NumericsCoreParams::tf() const
	{
		std::map<std::string, std::string>::const_iterator it(m_parameters.find("tf"));
		return it != m_parameters.end() ? std::stod(it->second) : 0;
	}

}