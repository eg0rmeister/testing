# Compiler

## Описание

В проекте используется cmake для сборки программы, поэтому перед использованием нужно выполнить:

`$ cmake .`

В проекте есть тесты для проверки работы различных этапов преобразования РВ в ДКА.

Можно выполнить сборку для всех целей:

`$ make`

и запустить все тесты:

`$ make test`

Собрать тест <test_name>:

`$ make <test_name>`

Запустить <test_name>:

`$ ./tests/exec/<test_name>`

## Использование

Вот пример кода, преобразующий массив РВ в лес ДКА:

```cpp
#include <DFA.h>
#include <DFA_Forest.h>
#include <NFA.h>
#include <NFA_to_DFA.h>
#include <REGTree.h>
#include <REG_to_NFA.h>

#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

int main() {
  // Create array of regular expressions
  std::string regs[] = {"abc*", "ab*c"};

  std::vector<DFA> dfa_vector;
  for (const auto& reg : regs) {
    // Build parse tree
    auto reg_tree = REGTree(reg);
    // Create NFA from tree
    auto nfa = GetNFAFromREG(reg_tree);
    // Remove epsilon-transitions from NFA
    auto clean_nfa = GetNFAWithNoEpsilons(nfa);
    // Convert NFA to DFA using Thompson's algorithm 
    auto dfa = ConvertNFAtoDFA(clean_nfa);
    // Print this DFA
    dfa.Visualize();
    // Save it
    dfa_vector.push_back(dfa);
  }

  // Create DFAForest - forest of automatons
  DFAForest forest(dfa_vector);

  return 0;  
}

```