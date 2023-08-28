export module stubby;
import hai;
import jute;
import missingno;
import sires;

namespace stbi {
struct deleter {
  void operator()(unsigned char *ptr) const;
};
using uc_ptr = hai::value_holder<unsigned char *, deleter>;

struct image {
  int width;
  int height;
  int num_channels;
  uc_ptr data;
};

export mno::req<image> load(const char *fname);
export mno::req<image> load_from_resource(jute::view fname);

export struct pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
};
static_assert(sizeof(pixel) == 4);
export void write_rgba(const char *fname, unsigned x, unsigned y,
                       const hai::array<pixel> &data);
} // namespace stbi

#pragma ecow add_impl load
#pragma ecow add_impl write
