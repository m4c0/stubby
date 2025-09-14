#pragma leco app
#pragma leco add_resource "test.png"
#pragma leco add_resource "test.ttf"

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

  auto font = stbtt::load_from_resource("test.ttf");

  stbi::write_rgba("out/test.png", w, h, data);
}

int main(int argc, char **argv) {
  stbi::load_from_resource("test.png")
      .map([](auto &&img) {
        silog::log(silog::info, "Resource image: %dx%d", img.width, img.height);
      })
      .trace("loading resource image")
      .log_error();

  test_write();

  if (argc < 2) {
    silog::log(silog::warning, "Pass an extra arg to test with a file in-disk");
    return 0;
  }

  stbi::load(argv[1])
      .map([](auto &&img) {
        silog::log(silog::info, "Image: %dx%d", img.width, img.height);
      })
      .trace("loading image")
      .log_error();
}
