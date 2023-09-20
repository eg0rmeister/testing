include(CTest)

include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/src)

add_executable(test_state test.cpp ${PROJECT_SOURCE_DIR}/src/DFA.cpp ${PROJECT_SOURCE_DIR}/include/DFA.h ${PROJECT_SOURCE_DIR}/src/State.cpp ${PROJECT_SOURCE_DIR}/include/State.h ${PROJECT_SOURCE_DIR}/src/Transition.cpp ${PROJECT_SOURCE_DIR}/include/Transition.h)

add_test(NAME "TestState" COMMAND test_state)