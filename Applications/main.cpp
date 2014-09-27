#include <iostream>
#include "Numerics/Mesh/Grid.hpp"

#include "Physics/Components/PhysicsConfiguration.hpp"
#include "Physics/Components/PhysicsCoreConfiguration.hpp"
#include "Physics/PhysicsModel.hpp"
#include <memory>

int main(int argc, char* argv[])
{
	if (argc != 3)
	{
		std::cerr << "Usage: " << argv[0] << " Physics PhysicsCore" << std::endl;
		return 1;
	}

	std::cout << "Hello World!" << std::endl;

	Grid g1, g2(10, 10, 1.0, 1.0);

	std::vector<double> v(0);
	std::cout << "size = " << v.size() << std::endl;

	v.resize(2);
	std::cout << "size = " << v.size() << std::endl;

	try
	{
		std::unique_ptr<PhysicsConfiguration> physConf(Physics(argv[1]));
		std::unique_ptr<PhysicsCoreConfiguration> physCoreConf(PhysicsCore(argv[2]));
		/*PhysicsConfiguration::Component_sequence compSeq = physConf->Component();
		for (PhysicsConfiguration::Component_const_iterator it = compSeq.begin(); it != compSeq.end(); it++)
		{
			std::cout << "Component " << it->name() << std::endl;
		}*/

		PhysicsModel pm(physConf, physCoreConf);
	}
	catch (const xml_schema::exception& e)
	{
		std::cerr << e << std::endl;
		//return 1;
	}

	

	std::cin.get();

	return 0;
}
