#include "Backend.hpp"

#include "Configuration/AppConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/ModelCoreConfiguration.hpp"

#include "Glacier/Glacier.hpp"
#include "Numerics/Algorithms/Primal.hpp"
#include "Utility/Logger/Logger.hpp"
#include <memory>

using namespace N_Configuration;
using namespace N_Glacier;
using namespace N_Mathematics;

void Backend::init(const std::string& aAppConfFileName)
{
	try
	{
		std::unique_ptr<AppConfiguration> appConf(App(aAppConfFileName));
		std::unique_ptr<ModelConfiguration> physConf;
		std::unique_ptr<ModelCoreConfiguration> physCoreConf;
		std::unique_ptr<ModelConfiguration> numericsConf;
		std::unique_ptr<ModelCoreConfiguration> numericsCoreConf;
		std::unique_ptr<AppConfiguration> loggerConf;

		N_Configuration::AppConfiguration::Parameter_sequence fileNames(appConf->Parameter());
		for (N_Configuration::AppConfiguration::Parameter_const_iterator it(fileNames.begin()); it != fileNames.end(); ++it)
		{
			if (!std::strcmp(it->name().c_str(), "Physics"))
				physConf = Model(*it);
			if (!std::strcmp(it->name().c_str(), "PhysicsCore"))
				physCoreConf = ModelCore(*it);
			if (!std::strcmp(it->name().c_str(), "Numerics"))
				numericsConf = Model(*it);
			if (!std::strcmp(it->name().c_str(), "NumericsCore"))
				numericsCoreConf = ModelCore(*it);
			if (!std::strcmp(it->name().c_str(), "Logger"))
				loggerConf = App(*it);
		}

		Logger::getInstance().init(loggerConf);
		Glacier::getInstance().init(physConf, physCoreConf);
		Primal::getInstance().init(numericsConf, numericsCoreConf);
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
