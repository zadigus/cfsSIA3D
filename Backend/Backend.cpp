#include "Backend.hpp"

#include <algorithm>
#include <functional>

#include "Glacier/Glacier.hpp"
#include "Numerics/Algorithms/Primal.hpp"
#include "Utility/Logger/Logger.hpp"

using namespace N_Configuration;
using namespace N_Glacier;
using namespace N_Mathematics;
using namespace std::placeholders;

void Backend::setModel(const N_Configuration::Parameter& a_Param, const ModelConf& a_ModelConf)
{
  if (!std::strcmp(a_Param.name().c_str(), "Physics"))
    a_ModelConf.m_PhysConf = Model(a_Param.data());
  if (!std::strcmp(a_Param.name().c_str(), "PhysicsCore"))
    a_ModelConf.m_PhysCoreConf = ModelCore(a_Param.data());
  if (!std::strcmp(a_Param.name().c_str(), "Numerics"))
    a_ModelConf.m_NumericsConf = Model(a_Param.data());
  if (!std::strcmp(a_Param.name().c_str(), "NumericsCore"))
    a_ModelConf.m_NumericsCoreConf = ModelCore(a_Param.data());
  if (!std::strcmp(a_Param.name().c_str(), "Logger"))
    a_ModelConf.m_LoggerConf = App(a_Param.data());
}

void Backend::init(const std::string& a_AppConfFileName)
{
	try
	{
    ModelConf modelConf;
    std::unique_ptr<AppConfiguration> appConf(App(a_AppConfFileName));
		N_Configuration::AppConfiguration::Parameter_sequence fileNames(appConf->Parameter());
    std::for_each(fileNames.begin(), fileNames.end(), std::bind(&Backend::setModel, this, _1, modelConf));

    Logger::getInstance().init(std::move(modelConf.m_LoggerConf));
    Glacier::getInstance().init(std::move(modelConf.m_PhysConf), std::move(modelConf.m_PhysCoreConf));
    Primal::getInstance().init(std::move(modelConf.m_NumericsConf), std::move(modelConf.m_NumericsCoreConf));
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
