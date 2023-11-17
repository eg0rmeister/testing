#pragma once
#include <map>
#include <stack>
#include <string>
#include <vector>

class StackMemory {
 public:
  void Declare(const std::string& name, int value);

  void Set(const std::string& name, int value);
  
  int Get(const std::string& name, int value);

  void Scope_in();

  void Scope_out();

 private:
  bool CheckDeclared(const std::string& name);

  std::string _declare_delimiter = "{";

  std::vector<std::string> _declare_history;
  std::map<std::string, std::stack<int>> _variables_history;
};