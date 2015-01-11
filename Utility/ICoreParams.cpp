#include "ICoreParams.hpp"

#include <algorithm>
#include <functional>

#include "Utility/Logger/Logger.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

using namespace std::placeholders;

ICoreParams::ICoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aCoreConf)
{
	if (!aCoreConf)
	{
		LOG_ERR("Core parameters not specified.");
		exit(EXIT_FAILURE);
	}

	N_Configuration::ModelCoreConfiguration::Parameter_sequence paramSeq = aCoreConf->Parameter();
	std::for_each(paramSeq.begin(), paramSeq.end(), std::bind(&ICoreParams::setParameter, this, _1));
}

ICoreParams::~ICoreParams()
{

}

void ICoreParams::setParameter(const N_Configuration::Parameter& aParam)
{
	m_Parameters.emplace(aParam.name(), aParam.data());
}