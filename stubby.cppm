module;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

export module stubby;
import hai;
import missingno;
import sires;
import traits;

namespace stbi {
static constexpr const auto num_channels = 4;

struct deleter {
  void operator()(unsigned char *ptr) { stbi_image_free(ptr); }
};
using uc_ptr = hai::value_holder<unsigned char *, deleter>;

struct image {
  int width;
  int height;
  int num_channels;
  uc_ptr data;
};

export mno::req<image> load(const char *fname) {
  image res{};
  res.data = uc_ptr{stbi_load(fname, &res.width, &res.height, &res.num_channels,
                              num_channels)};
  return (*res.data == nullptr) ? mno::req<image>::failed(stbi_failure_reason())
                                : mno::req<image>{traits::move(res)};
}
} // namespace stbi
