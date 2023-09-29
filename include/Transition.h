#pragma once

#include <State.h>
#include <UniqueObject.h>

#include <string>

class Transition : public UniqueObject {
 public:
  using state_ptr = State*;
  Transition(state_ptr target);
  Transition(std::string input, state_ptr target);
  std::string Input() const;
  const State* Target() const;

 private:
  std::string _input;
  state_ptr _target;
};

bool operator==(const Transition& lhs, const Transition& rhs);

// Instantiate Hash for Transition to store Transition objects in unordered sets
// and maps
template <>
struct std::hash<Transition> {
  std::size_t operator()(const Transition& transition) const;
};