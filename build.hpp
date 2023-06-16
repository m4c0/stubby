#include "../ecow/ecow.hpp"
#include "../hai/build.hpp"
#include "../missingno/build.hpp"
#include "../silog/build.hpp"
#include "../sires/build.hpp"

auto stubby() {
  using namespace ecow;

  auto m = unit::create<mod>("stubby");
  m->add_wsdep("hai", hai());
  m->add_wsdep("missingno", missingno());
  m->add_wsdep("silog", silog());
  m->add_wsdep("sires", sires());
  return m;
}
