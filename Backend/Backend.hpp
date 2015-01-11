#ifndef BACKEND_HPP
#define BACKEND_HPP

#include <memory>
#include <string>
#include "Utility/Singleton.hpp"

#include "Configuration/AppConfiguration.hpp" // TODO: why is that necessary here? unique_ptr seem to be the problem
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

//namespace N_Configuration {
//	class Parameter;
//	class ModelConfiguration;
//	class ModelCoreConfiguration;
//	class AppConfiguration;
//}

class Backend : public Singleton<Backend>
{
	friend class Singleton<Backend>;

	public:
		void init(const std::string& aAppConfFileName);
		void run();

	private:
		// Configuration setup
		void setModel(const N_Configuration::Parameter& aParam);

	private:
		// XML configuration parsers
		std::unique_ptr<N_Configuration::ModelConfiguration> m_PhysConf;
		std::unique_ptr<N_Configuration::ModelCoreConfiguration> m_PhysCoreConf;
		std::unique_ptr<N_Configuration::ModelConfiguration> m_NumericsConf;
		std::unique_ptr<N_Configuration::ModelCoreConfiguration> m_NumericsCoreConf;
		std::unique_ptr<N_Configuration::AppConfiguration> m_LoggerConf;
};

#endif