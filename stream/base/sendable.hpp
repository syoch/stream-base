#pragma once

#include <cinttypes>
#include <vector>

namespace stream {
class Sendable {
  bool send_trace_enabled = false;

 public:
  virtual ~Sendable();

  inline bool IsSendTraceEnabled() const { return this->send_trace_enabled; }
  inline void SetSendTraceEnabled(bool enabled) {
    this->send_trace_enabled = enabled;
  }

  virtual size_t Send(const std::vector<uint8_t> &buf) = 0;

  template <int N>
  size_t Send(const char (&buf)[N]) {
    std::vector<uint8_t> v{buf, buf + N};
    return this->Send(v);
  }

  void SendChar(const char ch) {
    std::vector<uint8_t> c(1);
    c[0] = ch;
    this->Send(c);
  }

  void SendU16(const uint16_t value) {
    std::vector<uint8_t> buf(2);
    buf[0] = (value >> 8) & 0xff;
    buf[1] = value & 0xff;

    this->Send(buf);
  }

  void SendU32(const uint32_t value) {
    std::vector<uint8_t> buf(4);
    buf[0] = (value >> 24) & 0xff;
    buf[1] = (value >> 16) & 0xff;
    buf[2] = (value >> 8) & 0xff;
    buf[3] = value & 0xff;

    this->Send(buf);
  }
};
}  // namespace stream