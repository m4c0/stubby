import silog;
import stubby;

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;

  return stbi::load(argv[1])
      .map([](auto &&img) {
        silog::log(silog::info, "Image: %dx%d", img.width, img.height);
        return 0;
      })
      .take([](auto msg) {
        silog::log(silog::error, "Failed loding image: %s", msg);
        return 1;
      });
}
