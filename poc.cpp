import silog;
import stubby;

int main(int argc, char **argv) {
  stbi::load_from_resource("test.png")
      .map([](auto &&img) {
        silog::log(silog::info, "Resource image: %dx%d", img.width, img.height);
      })
      .take([](auto msg) {
        silog::log(silog::error, "Failed loading resource image: %s", msg);
      });

  if (argc < 2) {
    silog::log(silog::warning, "Pass an extra arg to test with a file in-disk");
    return 0;
  }

  stbi::load(argv[1])
      .map([](auto &&img) {
        silog::log(silog::info, "Image: %dx%d", img.width, img.height);
      })
      .take([](auto msg) {
        silog::log(silog::error, "Failed loading image: %s", msg);
      });
}
