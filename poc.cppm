#pragma leco app
#pragma leco add_resource "test.png"
export module poc;

import silog;
import stubby;

void test_write() {
  constexpr const auto w = 64;
  constexpr const auto h = 32;
  stbi::pixels data{w * h};
  for (auto y = 0U; y < h; y++) {
    for (auto x = 0U; x < w; x++) {
      data[y * w + x] = {
          .r = static_cast<unsigned char>(x * 4),
          .g = static_cast<unsigned char>(y * 8),
          .b = 255,
          .a = 255,
      };
    }
  }
  stbi::write_rgba("out/test.png", w, h, data);
}

extern "C" int main(int argc, char **argv) {
  stbi::load_from_resource("test.png")
      .map([](auto &&img) {
        silog::log(silog::info, "Resource image: %dx%d", img.width, img.height);
      })
      .take([](auto msg) {
        silog::log(silog::error, "Failed loading resource image: %s",
                   msg.cstr().data());
      });

  test_write();

  if (argc < 2) {
    silog::log(silog::warning, "Pass an extra arg to test with a file in-disk");
    return 0;
  }

  stbi::load(argv[1])
      .map([](auto &&img) {
        silog::log(silog::info, "Image: %dx%d", img.width, img.height);
      })
      .take([](auto msg) {
        silog::log(silog::error, "Failed loading image: %s", msg.cstr().data());
      });
}
