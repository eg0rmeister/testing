#pragma once

#include <State.h>
#include <UniqueObject.h>

#include <string>

class Transition : public UniqueObject {
 public:
  /// @brief Create new epsilon-transition to state 'target'
  /// @param target Destination of transition
  Transition(State target);

  /// @brief Create new transition by letter 'input' to state 'target'
  /// @param input Letter from alphabet (not necessarily one character)
  /// @param target Destination of transition
  Transition(std::string input, State target);
  
  /// @brief Get letter by which transition is done
  /// @return std::string Letter of transition
  std::string Input() const;

  /// @brief Get destination of transition
  /// @return State object - destination
  const State& Target() const;

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