cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER)

enable_testing()
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH exec)
add_executable(main main.cpp src/FSA.cpp include/FSA.h src/NFA.cpp include/NFA.h src/DFA.cpp include/DFA.h src/State.cpp include/State.h src/Transition.cpp include/Transition.h src/UniqueObject.cpp include/UniqueObject.h src/NFA_to_DFA.cpp include/NFA_to_DFA.h  src/REG_to_NFA.cpp include/REG_to_NFA.h src/DFA_Forest.cpp include/DFA_Forest.h src/REGTree.cpp include/REGTree.h)