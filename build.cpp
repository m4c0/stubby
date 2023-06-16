#include "build.hpp"

int main(int argc, char **argv) {
  using namespace ecow;

  auto poc = unit::create<tool>("poc");
  poc->add_wsdep("silog", silog());
  poc->add_ref(stubby());
  poc->add_unit<>("poc");
  return run_main(poc, argc, argv);
}
