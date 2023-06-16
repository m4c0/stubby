import hai;
import silog;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

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

image load(const char *fname) {
  image res{};
  res.data = uc_ptr{stbi_load(fname, &res.width, &res.height, &res.num_channels,
                              num_channels)};
  return res;
}
} // namespace stbi

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;

  auto img = stbi::load(argv[1]);
  if (*img.data == nullptr)
    return 1;

  silog::log(silog::info, "Image: %dx%d", img.width, img.height);
}
