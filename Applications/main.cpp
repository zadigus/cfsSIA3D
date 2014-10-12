#include <iostream>
#include "Numerics/Mesh/Grid.hpp"

#include "Configuration/AppConfiguration.hpp"
#include "Configuration/ModelConfiguration.hpp"
#include "Configuration/PhysicsCoreConfiguration.hpp"
#include "Glacier/Glacier.hpp"
#include "Glacier/GlacierComponents/Geometry/Geometry.hpp"
#include "Numerics/Mesh/Grid.hpp"
#include <memory>

int main(int argc, char* argv[]) // TODO: I need a front-end and a back-end; use decorator pattern to decorate the backend with the frontend
{
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " ConfigFile" << std::endl;
		return 1;
	}

	/*std::cout << "Hello World!" << std::endl;

	Grid g1, g2(10, 10, 1.0, 1.0);

	std::vector<double> v(0);
	std::cout << "size = " << v.size() << std::endl;

	v.resize(2);
	std::cout << "size = " << v.size() << std::endl;*/

	try
	{
		std::unique_ptr<N_Configuration::AppConfiguration> appConf(N_Configuration::App(argv[1]));

		std::unique_ptr<N_Configuration::ModelConfiguration> physConf;
		std::unique_ptr<N_Configuration::PhysicsCoreConfiguration> physCoreConf;
		std::unique_ptr<N_Configuration::ModelConfiguration> mathConf;

		N_Configuration::AppConfiguration::Parameter_sequence fileNames(appConf->Parameter());
		for (N_Configuration::AppConfiguration::Parameter_const_iterator it = fileNames.begin(); it != fileNames.end(); ++it)
		{
			//std::cout << it->name() << ", " << *it << std::endl;
			if (!std::strcmp(it->name().c_str(), "Physics"))
				physConf = N_Configuration::Model(*it);
			if (!std::strcmp(it->name().c_str(), "PhysicsCore"))
				physCoreConf = N_Configuration::PhysicsCore(*it);
			if (!std::strcmp(it->name().c_str(), "Maths"))
				mathConf = N_Configuration::Model(*it);
		}

		N_Glacier::Glacier& g = N_Glacier::Glacier::getInstance();
		g.init(physConf, physCoreConf);
		//g.G()->print();
		//g.H()->Set(10);
		//g.G()->print();

	}
	catch (const xml_schema::exception& e)
	{
		std::cerr << e << std::endl;
		//return 1;
	}

	

	std::cin.get();

	return 0;
}
