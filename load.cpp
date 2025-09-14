module;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma GCC diagnostic pop

module stubby;
import hai;

namespace stbi {
  void deleter::operator()(unsigned char *ptr) const { stbi_image_free(ptr); }
  using uc_ptr = hai::value_holder<unsigned char *, deleter>;
}

stbi::image stbi::load(const char * data, unsigned sz) {
  auto d = reinterpret_cast<const unsigned char *>(data);

  image res {};
  res.data = uc_ptr {
    stbi_load_from_memory(d, sz, &res.width, &res.height, &res.num_channels, 4)
  };
  return res;
}

