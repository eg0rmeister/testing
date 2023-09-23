#include "UniqueObject.h"

uint32_t UniqueObject::_global_id = 0;

UniqueObject::UniqueObject(): _id(_global_id++) {}

uint32_t UniqueObject::ID() const { return this->_id; }