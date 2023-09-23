# Compiler

Инструкция по запуску:

`$ cmake .`

Выполнить сборку для всех целей:

`$ make`

Запустить все тесты:

`$ make test`

Собрать тест <test_name>:

`$ make <test_name>`

Запустить <test_name>:

`$ ./tests/exec/<test_name>`

TODO:
* Функция `Merge()` для объединения двух НКА
* Функция `add_eps_transition` - обёртка над `AddTransition` для НКА
* ...