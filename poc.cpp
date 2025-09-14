#pragma leco app
#pragma leco add_resource "test.png"
import jute;
import hai;
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

  stbi::write_rgba("out/test.png", w, h, data);
}

void test_read() {
  sires::read("test.png", nullptr, [](void * ptr, hai::array<char> & bits) {
    auto img = stbi::load(bits.begin(), bits.size());
    silog::log(silog::info, "Resource image: %dx%d", img.width, img.height);
  });
}

#ifdef LECO_TARGET_WASM
int main() {
  test_read();
}
#else
int main(int argc, char **argv) {
  test_read();
  test_write();

  if (argc < 2) {
    silog::log(silog::warning, "Pass an extra arg to test with a file in-disk");
    return 0;
  }

  sires::read(jute::view::unsafe(argv[1]), nullptr, [](void * ptr, hai::array<char> & bits) {
    auto img = stbi::load(bits.begin(), bits.size());
    silog::log(silog::info, "Image: %dx%d", img.width, img.height);
  });
}
#endif
