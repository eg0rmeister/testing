#ifndef COMPILER_TRANSITION_H
#define COMPILER_TRANSITION_H

#include <State.h>
#include <UniqueObject.h>

#include <string>

class Transition : public UniqueObject {
 public:
  Transition(std::string input, State target);
  std::string Input() const;
  State Target() const;

 private:
  std::string _input;
  State _target;
};

bool operator==(const Transition& lhs, const Transition& rhs);

// Instantiate Hash for Transition to store Transition objects in unordered sets
// and maps
template <>
struct std::hash<Transition> {
  std::size_t operator()(const Transition& transition) const;
};

#endif