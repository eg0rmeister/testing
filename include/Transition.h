#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H

#include <UniqueObject.h>

#include <string>

class Transition : public UniqueObject {
 public:
  Transition();

 private:
};

bool operator==(const Transition& lhs, const Transition& rhs);

// Instantiate Hash for Transition to store Transition objects in unordered sets
// and maps
template <>
struct std::hash<Transition> {
  std::size_t operator()(const Transition& transition) const;
};

#endif