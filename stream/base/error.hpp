#pragma once

#include <stdexcept>

namespace stream {
class ConnectionClosedError : public std::runtime_error {
 public:
  ConnectionClosedError() : std::runtime_error("Connection closed") {}
};
}  // namespace stream