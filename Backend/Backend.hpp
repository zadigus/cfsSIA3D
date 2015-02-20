#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <memory>
#include <string>
#include "Utility/Singleton.hpp"

#include "Configuration/AppConfiguration.hpp" // this is necessary here because these files are generated
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

typedef struct ModelConf
{
  // XML configuration parsers
  std::unique_ptr<N_Configuration::ModelConfiguration> m_PhysConf;
  std::unique_ptr<N_Configuration::ModelCoreConfiguration> m_PhysCoreConf;
  std::unique_ptr<N_Configuration::ModelConfiguration> m_NumericsConf;
  std::unique_ptr<N_Configuration::ModelCoreConfiguration> m_NumericsCoreConf;
  std::unique_ptr<N_Configuration::AppConfiguration> m_LoggerConf;
} ModelConf;

class Backend : public Singleton<Backend>
{
	friend class Singleton<Backend>;

	public:
    void init(const std::string& a_AppConfFileName);
		void run();

	private:
		// Configuration setup
    void setModel(const N_Configuration::Parameter& a_Param, const ModelConf& a_ModelConf);
};

#endif
