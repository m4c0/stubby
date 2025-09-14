export module stubby;
import hai;
import jute;

namespace stbi {
  struct error {};
  struct invalid_image_size {};
  struct unsupported_file_extension {};

struct deleter {
  void operator()(unsigned char *ptr) const;
};
using uc_ptr = hai::value_holder<unsigned char *, deleter>;

export struct image {
  int width;
  int height;
  int num_channels;
  uc_ptr data;
};

export image load(const char * data, unsigned size);
export image info(const char * data, unsigned size);

export struct pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};
static_assert(sizeof(pixel) == 4);
export using pixels = hai::array<pixel>;
export void write_rgba(const char *fname, unsigned x, unsigned y,
                       const pixels &data);

static_assert(sizeof(unsigned) == 4);
export using pixels_u = hai::array<unsigned>;
export void write_rgba(const char *fname, unsigned x, unsigned y,
                       const pixels_u &data);

export void write_rgba_unsafe(const char *fname, unsigned x, unsigned y,
                              const pixel *data);
} // namespace stbi

#pragma leco add_impl load
#pragma leco add_impl write
