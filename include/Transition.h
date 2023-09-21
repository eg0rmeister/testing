#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H

#include <string>

class Transition {
 public:
  Transition();
  uint32_t ID() const;
 private:
  uint32_t _id;
  static uint32_t _global_id;
};

bool operator==(const Transition& lhs, const Transition& rhs);

// Instantiate Hash for Transition to store Transition objects in unordered sets and maps
template <>
struct std::hash<Transition> {
  std::size_t operator()(const Transition& transition) const;
};

#endif