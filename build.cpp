#include "../ecow/ecow.hpp"
#include "../hai/build.hpp"
#include "../missingno/build.hpp"
#include "../silog/build.hpp"
#include "../sires/build.hpp"

int main(int argc, char **argv) {
  using namespace ecow;

  auto poc = unit::create<tool>("poc");
  poc->add_wsdep("hai", hai());
  poc->add_wsdep("missingno", missingno());
  poc->add_wsdep("silog", silog());
  poc->add_wsdep("sires", sires());
  poc->add_unit<>("poc");
  return run_main(poc, argc, argv);
}
