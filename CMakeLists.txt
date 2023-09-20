cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test main.cpp src/DFA.cpp include/DFA.h src/State.cpp include/State.h src/Transition.cpp include/Transition.h)