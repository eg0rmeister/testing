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

В проекте есть инструменты для:
* Построения дерева разбора по регулярному выражению - за это отвечает класс `REGTree`;
* Построения НКА по дереву РВ - для этого есть функция `GetNFAFromREG`, принимающая объект `REGTree` и возвращающая `NFA`;
* Удаления переходов по пустым словам из НКА - `GetNFAWithNoEpsilons`;
* Получения по НКА эквивалентного ему ДКА с помощью алгоритма Томпсона - `ConvertNFAtoDFA`, возвращает объект класса `DFA`;
* Построения леса ДКА. Это структура, позволяющая параллельно совершать переходы по нескольким ДКА.

На данный момент для работы некоторых алгоритмов важно, что одна буква алфавита - это один символ (`char`), но это не обязательно должен быть символ латинского алфавита. Символ `~` зарезервирован для обозначения эпсилон-перехода.

И НКА, и ДКА с точки зрения реализации не являются полными, то есть явно могут храниться не все переходы. 
Но попытка перейти из состояния по букве, по которой не было перехода, по умолчанию приводит в тупиковое непринимающее состояние Trash, из которого нельзя вернуться.

## Использование

Вот пример кода, преобразующий массив РВ в лес ДКА, из файла `main.cpp`:

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

  // Check if any of DFA's accepts following words
  std::cout << std::boolalpha << forest.TestWord("ab") << '\n';     // true
  std::cout << std::boolalpha << forest.TestWord("abc") << '\n';    // true
  std::cout << std::boolalpha << forest.TestWord("abbc") << '\n';   // true
  std::cout << std::boolalpha << forest.TestWord("ababc") << '\n';  // false

  return 0;
}

```