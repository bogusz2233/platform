#pragma once

#include <stdarg.h>
#include <stdint.h>
#include <variant>

namespace drivers {

enum class Status {
  SUCCESS          = 0,
  FAIL             = -1,
  NOT_IMPLEMENTED  = -2,
  NULLPTR          = -3,
  INVALID_ARGUMENT = -4,
};

using Result = std::variant<Status, uint32_t>;

class Driver {
public:
  Result Read(void *data, uint32_t size);
  Result Write(const void *data, uint32_t size);

private:
  virtual Result ReadImpl(void *data, uint32_t size);
  virtual Result WriteImpl(const void *data, uint32_t size);
};

} // namespace drivers
