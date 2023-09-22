include(CTest)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

set (EXECUTABLE_OUTPUT_PATH exec)
add_executable(test_state test.cpp ${PROJECT_SOURCE_DIR}/src/FSA.cpp ${PROJECT_SOURCE_DIR}/include/FSA.h ${PROJECT_SOURCE_DIR}/src/NFA.cpp ${PROJECT_SOURCE_DIR}/include/NFA.h ${PROJECT_SOURCE_DIR}/src/DFA.cpp ${PROJECT_SOURCE_DIR}/include/DFA.h ${PROJECT_SOURCE_DIR}/src/State.cpp ${PROJECT_SOURCE_DIR}/include/State.h ${PROJECT_SOURCE_DIR}/src/Transition.cpp ${PROJECT_SOURCE_DIR}/include/Transition.h  ${PROJECT_SOURCE_DIR}/src/UniqueObject.cpp ${PROJECT_SOURCE_DIR}/include/UniqueObject.h)

add_test(NAME "TestState" COMMAND test_state)