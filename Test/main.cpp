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
  g.Refine(0.5);
  Export(g, "out.grid");

  size_t x(0); size_t y(1);
  cout << "Value = " << g(x, y) << endl; // TODO: that shouldn't compile ...

  cin.get();

	return EXIT_SUCCESS;
}
