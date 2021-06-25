cmake_minimum_required(VERSION 3.0)
project(Testes-EDI)

set(CMAKE_CXX_STANDARD 11)

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTestsArrayList testArrayList.cpp)
add_executable(runTestsLinkedList testLinkedList.cpp)

target_link_libraries(runTestsArrayList ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTestsLinkedList ${GTEST_LIBRARIES} pthread)
