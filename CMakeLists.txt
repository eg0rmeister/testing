cmake_minimum_required(VERSION 3.9)
project(compiler)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_COMPILER)

enable_testing()
add_subdirectory(tests)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/src AllCompiler)
link_libraries(AllCompiler)

set (EXECUTABLE_OUTPUT_PATH exec)
add_executable(main main.cpp)