module;
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

export module stubby;
import hai;
import missingno;
import silog;
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

stbi_io_callbacks yoyo_callbacks{
    .read = [](void *user, char *data, int size) -> int { return 0; },
    .skip = [](void *user, int n) -> void {},
    .eof = [](void *user) -> int { return 0; },
};

inline mno::req<image> load_from(auto fn, auto... args) {
  image res{};
  res.data = uc_ptr{
      fn(args..., &res.width, &res.height, &res.num_channels, num_channels)};
  return (*res.data == nullptr) ? mno::req<image>::failed(stbi_failure_reason())
                                : mno::req<image>{traits::move(res)};
}
export mno::req<image> load(const char *fname) {
  return load_from(stbi_load, fname);
}
export mno::req<image> load_from_resource(jute::view fname) {
  return sires::open(fname).fmap([](auto &rdr) {
    return load_from(stbi_load_from_callbacks, &yoyo_callbacks, &rdr);
  });
}
} // namespace stbi
