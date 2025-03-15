cmake_minimum_required(VERSION 3.20)

project(HW9 CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dijkstra's Algorithm Source Files
set(DIJKSTRAS_SRC_FILES
    src/dijkstras.h
    src/dijkstras.cpp
)

add_executable(dijkstra_main
    ${DIJKSTRAS_SRC_FILES}
    src/dijkstras_main.cpp
)

# Word Ladder Source Files
set(LADDER_SRC_FILES
    src/ladder.h
    src/ladder.cpp
)

add_executable(ladder_main
    ${LADDER_SRC_FILES}
    src/ladder_main.cpp
)

# Automatically Fetch Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

# Enable ASan and UBSan
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(SANITIZER_FLAGS "-fsanitize=address,undefined -fno-omit-frame-pointer")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
endif()

# Test Executable
set(STUDENT_TEST_FILES
    gtest/gtestmain.cpp
    gtest/student_gtests.cpp
)

add_executable(student_gtests 
    ${STUDENT_TEST_FILES}
    ${DIJKSTRAS_SRC_FILES}
    ${LADDER_SRC_FILES}
)

# Ensure `src/` is included
target_include_directories(student_gtests PRIVATE ${CMAKE_SOURCE_DIR}/src ${CMAKE_SOURCE_DIR}/gtest)

# Link against Google Test and add sanitizers
target_link_libraries(student_gtests PRIVATE GTest::gtest GTest::gtest_main pthread ${SANITIZER_FLAGS})
