module;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#pragma GCC diagnostic pop

module stubby;
import hai;
import jute;
import silog;

void stbi::write_rgba(const char *fname, unsigned w, unsigned h,
                      const hai::array<pixel> &data) {
  if (data.size() != w * h)
    return;

  auto [stem, ext] = jute::view::unsafe(fname).rsplit('.');
  if (ext == "png") {
    stbi_write_png(fname, w, h, 4, data.begin(), w * sizeof(pixel));
  } else if (ext == "bmp") {
    stbi_write_bmp(fname, w, h, 4, data.begin());
  } else if (ext == "tga") {
    stbi_write_tga(fname, w, h, 4, data.begin());
  } else if (ext == "jpg") {
    stbi_write_jpg(fname, w, h, 4, data.begin(), 75);
  }
}
