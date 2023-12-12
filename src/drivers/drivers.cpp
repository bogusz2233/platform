#include <drivers.h>

namespace drivers {

Result Driver::Read(void *data, uint32_t size) {
  if (data == nullptr) {
    return Status::NULLPTR;
  }

  if (size == 0) {
    return Status::INVALID_ARGUMENT;
  }

  return ReadImpl(data, size);
}

Result Driver::Write(const void *data, uint32_t size) {
  if (data == nullptr) {
    return Status::NULLPTR;
  }

  if (size == 0) {
    return Status::INVALID_ARGUMENT;
  }

  return WriteImpl(data, size);
}

Result Driver::ReadImpl(void *data, uint32_t size) { return Status::NOT_IMPLEMENTED; }
Result Driver::WriteImpl(const void *data, uint32_t size) { return Status::NOT_IMPLEMENTED; }

} // namespace drivers