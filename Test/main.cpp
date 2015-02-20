#include <iostream>
#include <cassert>

#include "Numerics/Mesh/Grid.hpp"

using namespace std;

int main(int argc, char* argv[])
{ 
  if(argc != 2)
  {
    cerr << "Usage: " << argv[0] << " PATH-TO-GRID-FILE" << endl;
    return EXIT_FAILURE;
  }
  cout << "Hello World!" << endl;

  Grid g(argv[1]);
  g.refine(0.5);
  toGrid(g, "out.grid");

  size_t x(0); double y(1);
  cout << "Value = " << g(0, x) << endl;

  cin.get();

	return EXIT_SUCCESS;
}
