#pragma once

#include <cinttypes>

#include <vector>
#include <algorithm>

#include "./types.hpp"

namespace stream {
class Receivable {
  bool recv_trace_enabled = false;

 public:
  virtual ~Receivable();

  inline bool IsRecvTraceEnabled() const { return this->recv_trace_enabled; }
  inline void SetRecvTraceEnabled(bool enabled) {
    this->recv_trace_enabled = enabled;
  }

  virtual size_t Recv(std::vector<uint8_t> &buf,
                      DeltaTimeMs timeout = 1000) = 0;

  char RecvChar(DeltaTimeMs timeout = 1000) {
    std::vector<uint8_t> c{0};
    this->Recv(c, timeout);
    return c[0];
  }

  void RecvExactly(std::vector<uint8_t> &buf, DeltaTimeMs timeout = 1000) {
    size_t read = 0;
    auto size = buf.size();
    while (read < size) {
      std::vector<uint8_t> sub_vector{buf.begin() + read, buf.end()};
      auto chunk_size = this->Recv(sub_vector, timeout);

      std::copy(sub_vector.begin(), sub_vector.end(), buf.begin() + read);

      read += chunk_size;
    }
  }

  std::vector<uint8_t> RecvUntil(char delim, DeltaTimeMs timeout = -1) {
    std::vector<uint8_t> ret;
    while (true) {
      auto c = this->RecvChar(timeout);
      if (c == delim) {
        return ret;
      }
      ret.emplace_back(c);
    }
    return ret;
  }

  uint32_t RecvU32() {
    std::vector<uint8_t> buf(4);
    this->RecvExactly(buf);
    return buf[0] << 24 | buf[1] << 16 | buf[2] << 8 | buf[3];
  }
};
}  // namespace stream