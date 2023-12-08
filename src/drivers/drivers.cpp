#include <drivers.h>

namespace drivers {
  
  Result Driver::Read(const void *data, uint32_t size){
    if(data == nullptr){
      return Status::NULLPTR;
    }

    if(size == 0){
      return Status::INVALID_ARGUMENT;
    }

    return ReadImpl(data, size);
  }


Result Driver::ReadImpl(const void *data, uint32_t size){
  return Status::NOT_IMPLEMENTED;
}

}