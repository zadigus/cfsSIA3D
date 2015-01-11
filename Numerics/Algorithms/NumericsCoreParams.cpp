#include "NumericsCoreParams.hpp"

#include "Configuration/ModelCoreConfiguration.hpp"

namespace N_Mathematics {

	NumericsCoreParams::NumericsCoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aNumericsCoreConf) 
		: ICoreParams(aNumericsCoreConf)
	{

	}

	NumericsCoreParams::~NumericsCoreParams()
	{

	}

	double NumericsCoreParams::dt() const
	{
		return std::stod(m_Parameters.at("dt"));
	}

	double NumericsCoreParams::ti() const
	{
		return std::stod(m_Parameters.at("ti"));
	}

	double NumericsCoreParams::tf() const
	{
		return std::stod(m_Parameters.at("tf"));
	}

}