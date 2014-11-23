#include "Backend.hpp"
#include <iostream>

int main(int argc, char* argv[])
{ 
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " ConfigFile" << std::endl;
		return EXIT_FAILURE;
	}

	Backend::getInstance().init(argv[1]);
	Backend::getInstance().run();

	return EXIT_SUCCESS;
}
