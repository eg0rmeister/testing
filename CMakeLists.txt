cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER)

enable_testing()
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH exec)
add_executable(main main.cpp src/DFA.cpp include/DFA.h src/State.cpp include/State.h src/Transition.cpp include/Transition.h src/UniqueObject.cpp include/UniqueObject.h)