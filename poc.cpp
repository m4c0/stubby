import silog;
import stubby;

int main(int argc, char **argv) {
  if (argc < 2)
    return 1;

  auto img = stbi::load(argv[1]);
  if (*img.data == nullptr)
    return 1;

  silog::log(silog::info, "Image: %dx%d", img.width, img.height);
}
