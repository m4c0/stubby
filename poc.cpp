#pragma leco app
#pragma leco add_resource "test.png"
#pragma leco add_resource "test.ttf"

import jute;
import silog;
import sires;
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

  auto font = stbtt::load(sires::slurp("test.ttf").begin());

  stbi::write_rgba("out/test.png", w, h, data);
}

int main(int argc, char **argv) {
  auto bits = sires::slurp("test.png");
  auto img = stbi::load(bits.begin(), bits.size());
  silog::log(silog::info, "Resource image: %dx%d", img.width, img.height);

  test_write();

  if (argc < 2) {
    silog::log(silog::warning, "Pass an extra arg to test with a file in-disk");
    return 0;
  }

  bits = sires::slurp(jute::view::unsafe(argv[1]));
  img = stbi::load(bits.begin(), bits.size());
  silog::log(silog::info, "Image: %dx%d", img.width, img.height);
}
