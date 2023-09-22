#ifndef COMPILER_UNIQUEOBJECT_H
#define COMPILER_UNIQUEOBJECT_H

#include <stdint.h>

class UniqueObject {
 public:
  UniqueObject();
  uint32_t ID() const;
 private:
  uint32_t _id;
  static uint32_t _global_id;
};

#endif