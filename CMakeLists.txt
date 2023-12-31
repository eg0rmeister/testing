cmake_minimum_required(VERSION 3.7)

project("Antlr-cpp-driver")

set(HEADERS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Include")
set(GENERATED_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Generated")
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Sources")

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Compiler must be at least 17
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread") # pthread is important here

# Add external build for antlrcpp
include(ExternalAntlr4Cpp)
# Add antrl4cpp artifacts to project environment
include_directories(${ANTLR4_INCLUDE_DIRS})

# Set variable pointing to the antlr tool that supports C++
# This is not required if the jar file can be found under PATH environment
set(ANTLR_EXECUTABLE ${CMAKE_CURRENT_SOURCE_DIR}/tools/antlr-4.13.1-complete.jar)
find_package(ANTLR REQUIRED)

# CMake commands for this specific project start here
# Call macro to add lexer and grammar to your build dependencies.
antlr_target(ExprGrammarParser Expr.g4 VISITOR OUTPUT_DIRECTORY ${GENERATED_DIR})

# Add our project source directories
include_directories(${HEADERS_DIR} ${GENERATED_DIR})

add_executable(driver driver.cpp ${ANTLR_ExprGrammarParser_CXX_OUTPUTS})

# List all the cpp files used
target_sources(driver PUBLIC ${SOURCES_DIR}/InterpreterVisitor.cpp)

# Link required libraries
target_link_libraries(driver antlr4_static ${SYSTEM_LIBS})

# Copy the input file next to the generated executable
add_custom_command(TARGET driver POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/input.txt"
  $<TARGET_FILE_DIR:driver>)

