#pragma once

#include "receivable.hpp"
#include "sendable.hpp"

namespace stream {
class RecvAndSend : public Receivable, public Sendable {
 public:
  ~RecvAndSend() override;

  inline bool IsTraceEnabled() const {
    return this->IsRecvTraceEnabled() || this->IsSendTraceEnabled();
  }

  inline void SetTraceEnabled(bool enabled) {
    this->SetRecvTraceEnabled(enabled);
    this->SetSendTraceEnabled(enabled);
  }
};
}  // namespace stream