#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;

  auto fname = argv[1];

  static constexpr const auto num_channels = 4;

  int w;
  int h;
  int n;
  auto raw = stbi_load(fname, &w, &h, &n, num_channels);
  if (raw == nullptr)
    return 1;
}
