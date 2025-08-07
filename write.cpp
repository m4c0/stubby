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

static int write(const char *fname, unsigned w, unsigned h, const void *data) {
  auto [stem, ext] = jute::view::unsafe(fname).rsplit('.');
  if (ext == "png") {
    return stbi_write_png(fname, w, h, 4, data, w * sizeof(stbi::pixel));
  } else if (ext == "bmp") {
    return stbi_write_bmp(fname, w, h, 4, data);
  } else if (ext == "tga") {
    return stbi_write_tga(fname, w, h, 4, data);
  } else if (ext == "jpg") {
    return stbi_write_jpg(fname, w, h, 4, data, 75);
  } else {
    throw stbi::unsupported_file_extension {};
  }
}

void stbi::write_rgba(const char *fname, unsigned w, unsigned h,
                      const hai::array<pixel> &data) {
  if (data.size() != w * h) throw invalid_image_size {};
  if (!write(fname, w, h, data.begin())) throw error {};
}
void stbi::write_rgba(const char *fname, unsigned w, unsigned h,
                      const hai::array<unsigned> &data) {
  if (data.size() != w * h) throw invalid_image_size {};
  if (!write(fname, w, h, data.begin())) throw error {};
}
void stbi::write_rgba_unsafe(const char *fname, unsigned w, unsigned h,
                             const pixel *data) {
  if (!write(fname, w, h, data)) throw error {};
}
