module;
#pragma GCC diagnostic push
#define STB_TRUETYPE_IMPLEMENTATION
#include "stb_truetype.h"
#pragma GCC diagnostic pop
#undef assert

module stubby;

namespace stbtt {
  class font {
    stbtt_fontinfo m_info;

  public:
    font(const char * data) {
      auto * d = reinterpret_cast<const unsigned char *>(data);
      // This is the "no offset check" issue??
      auto n = stbtt_InitFont(&m_info, d, 0);
      if (!n) throw error {};
    }
  };

  void deleter::operator()(font * f) { delete f; }
  font_ptr load(const char * data) {
    return font_ptr { new font(data) };
  }
}
