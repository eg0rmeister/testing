#pragma once

#include <stdint.h>

class UniqueObject {
 public:
  UniqueObject();
  uint32_t ID() const;

 private:
  uint32_t _id;
  static uint32_t _global_id;
};