#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>	

int main(int argc, char* argv[])
{ 
	std::cout << "Hello World!" << std::endl;

  for(unsigned int i(3); i--; )
  {
    std::cout << i << std::endl;
  }

	std::cin.get();

	return EXIT_SUCCESS;
}
