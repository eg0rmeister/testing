#include <Transition.h>

Transition::Transition(State target) : Transition("~", target) {}

Transition::Transition(std::string input, State target)
    : UniqueObject(), _input(input), _target(target) {}

std::string Transition::Input() const { return _input; }

const State& Transition::Target() const { return _target; }

bool operator==(const Transition& lhs, const Transition& rhs) {
  return lhs.ID() == rhs.ID();
}

// Instantiate Hash for State to store State objects in unordered sets and maps

std::size_t std::hash<Transition>::operator()(
    const Transition& transition) const {
  // Use unique transition ID
  return transition.ID();
}
