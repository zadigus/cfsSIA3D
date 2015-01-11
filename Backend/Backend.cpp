#include "Backend.hpp"

#include <algorithm>
#include <functional>

#include "Configuration/AppConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Algorithms/Primal.hpp"
#include "Utility/Logger/Logger.hpp"

using namespace N_Configuration;
using namespace N_Glacier;
using namespace N_Mathematics;
using namespace std::placeholders;

void Backend::setModel(const N_Configuration::Parameter& aParam)
{
	if (!std::strcmp(aParam.name().c_str(), "Physics"))
		m_PhysConf = Model(aParam.data());
	if (!std::strcmp(aParam.name().c_str(), "PhysicsCore"))
		m_PhysCoreConf = ModelCore(aParam.data());
	if (!std::strcmp(aParam.name().c_str(), "Numerics"))
		m_NumericsConf = Model(aParam.data());
	if (!std::strcmp(aParam.name().c_str(), "NumericsCore"))
		m_NumericsCoreConf = ModelCore(aParam.data());
	if (!std::strcmp(aParam.name().c_str(), "Logger"))
		m_LoggerConf = App(aParam.data());
}

void Backend::init(const std::string& aAppConfFileName)
{
	try
	{
		std::unique_ptr<AppConfiguration> appConf(App(aAppConfFileName));
		N_Configuration::AppConfiguration::Parameter_sequence fileNames(appConf->Parameter());
		std::for_each(fileNames.begin(), fileNames.end(), std::bind(&Backend::setModel, this, _1));

		Logger::getInstance().init(m_LoggerConf);
		Glacier::getInstance().init(m_PhysConf, m_PhysCoreConf);
		Primal::getInstance().init(m_NumericsConf, m_NumericsCoreConf);
	}
	catch (const xml_schema::exception& e)
	{
		std::cerr << e << std::endl;
	}
}

void Backend::run()
{
	Primal::getInstance().run();
	std::cin.get();
}