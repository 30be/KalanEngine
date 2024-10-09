#include <iostream>

#include "engine/engine.hpp"
auto main(int /*argc*/, char * /*argv*/[]) -> int {
  std::cout << "hello!\n";
  engine Engine;
  Engine.Run();
  return 0;
}
