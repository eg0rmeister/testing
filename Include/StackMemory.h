#pragma once

#include <map>
#include <stack>
#include <string>
#include <vector>

#include "Printable.h"

class StackMemory {
 public:
  void Declare(const std::string& name, Printable value);

  void Set(const std::string& name, Printable value);
  
  Printable Get(const std::string& name);

  void Scope_in();

  void Scope_out();

 private:
  bool CheckDeclared(const std::string& name);

  std::string _declare_delimiter = "{";

  std::vector<std::string> _declare_history;
  std::map<std::string, std::stack<Printable>> _variables_history;
};