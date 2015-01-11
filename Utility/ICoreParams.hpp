#ifndef COREPARAMS_H_
#define COREPARAMS_H_

#include <memory>
#include <map>
#include <string>

namespace N_Configuration {
	class ModelCoreConfiguration;
	class Parameter;
}

struct ICoreParams
{
	ICoreParams(const std::unique_ptr<N_Configuration::ModelCoreConfiguration>& aCoreConf);
	virtual ~ICoreParams() = 0;

	void setParameter(const N_Configuration::Parameter& aParam);
	
	std::map<std::string, std::string> m_Parameters;
};

#endif