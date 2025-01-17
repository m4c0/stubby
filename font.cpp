module;
#pragma GCC diagnostic push
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#pragma GCC diagnostic pop
#undef assert

module stubby;
import silog;

namespace stbtt {
  class font {
    stbtt_fontinfo m_info;

  public:
    font(jute::view fname) {
      sires::slurp(fname)
        .map([this](auto & data) {
          auto * d = reinterpret_cast<unsigned char *>(data.begin());
          // This is the "no offset check" issue??
          return stbtt_InitFont(&m_info, d, 0);
        })
        .assert([](auto n) { return n != 0; },
                "Failed to open font")
        .map([](auto) {})
        .take([](auto msg) {
          silog::die("%.*s", static_cast<int>(msg.size()), msg.data());
        });
    }
  };

  void deleter::operator()(font * f) { delete f; }
  font_ptr load_from_resource(jute::view fname) {
    return font_ptr { new font(fname) };
  }
}
