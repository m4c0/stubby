module;
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#pragma GCC diagnostic pop

module stubby;
import hai;
import missingno;
import silog;
import sires;
import traits;

namespace stbi {
static constexpr const auto num_channels = 4;

void deleter::operator()(unsigned char *ptr) const { stbi_image_free(ptr); }
using uc_ptr = hai::value_holder<unsigned char *, deleter>;

stbi_io_callbacks yoyo_callbacks{
    .read = [](void *user, char *data, int size) -> int {
      return static_cast<yoyo::reader *>(user)
          ->read_up_to(data, size)
          .take([size](auto msg) {
            silog::log(silog::error, "Failed to read %d bytes of image: %s",
                       size, msg);
            return 0;
          });
    },
    .skip = [](void *user, int n) -> void {
      static_cast<yoyo::reader *>(user)
          ->seekg(n, yoyo::seek_mode::current)
          .take([](auto msg) {
            silog::log(silog::error, "Failed to seek image: %s", msg);
          });
    },
    .eof = [](void *user) -> int {
      return static_cast<yoyo::reader *>(user)
          ->eof()
          .map([](auto) { return 1; })
          .take([](auto msg) {
            silog::log(silog::error, "Failed to check EOF of image: %s", msg);
            return 0;
          });
    },
};

inline mno::req<image> load_from(auto fn, auto... args) {
  image res{};
  res.data = uc_ptr{
      fn(args..., &res.width, &res.height, &res.num_channels, num_channels)};
  return (*res.data == nullptr) ? mno::req<image>::failed(stbi_failure_reason())
                                : mno::req<image>{traits::move(res)};
}
mno::req<image> load(const char *fname) { return load_from(stbi_load, fname); }
mno::req<image> load_from_resource(jute::view fname) {
  return sires::open(fname).fmap([](auto &rdr) {
    return load_from(stbi_load_from_callbacks, &yoyo_callbacks, &*rdr);
  });
}
} // namespace stbi
