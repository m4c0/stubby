#include "../silog/build.hpp"
#include "build.hpp"

int main(int argc, char **argv) {
  using namespace ecow;

  auto poc = unit::create<app>("poc");
  poc->add_wsdep("silog", silog());
  poc->add_ref(stubby());
  poc->add_unit<>("poc");
  poc->add_resource("test.png");
  return run_main(poc, argc, argv);
}
