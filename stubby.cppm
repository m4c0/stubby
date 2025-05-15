export module stubby;
import hai;
import jute;
import missingno;
import silog;
import sires;

namespace stbi {
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

export mno::req<image> load(const char *fname);
export mno::req<image> load_from_resource(jute::view fname);
export void load(jute::view fname, void *, hai::fn<void, void *, const image &> callback);
export void load_from_resource(jute::view fname, void *, hai::fn<void, void *, const image &> callback);

export void info(jute::view fname, void *, hai::fn<void, void *, const image &> callback);
export void info_from_resource(jute::view fname, void *, hai::fn<void, void *, const image &> callback);

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

namespace stbtt {
  export class font;
  export struct deleter { void operator()(font *); };
  export using font_ptr = hai::value_holder<font *, deleter>;
  export font_ptr load_from_resource(jute::view fname);
}

#pragma leco add_impl font
#pragma leco add_impl load
#pragma leco add_impl write
