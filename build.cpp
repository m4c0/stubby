#include "ecow.hpp"

int main(int argc, char **argv) {
  using namespace ecow;

  auto poc = unit::create<app>("poc");
  poc->add_unit<box>("poc");
  poc->add_resource("test.png");
  return run_main(poc, argc, argv);
}
