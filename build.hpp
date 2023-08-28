#include "../ecow/ecow.hpp"

auto stubby() {
  using namespace ecow;

  return unit::create<box>("stubby");
}
