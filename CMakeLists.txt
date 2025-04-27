cmake_minimum_required(VERSION 3.10)
project(ZookeepersChallenge)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCE_FILES
    src/Animal.cpp
    src/Hyena.cpp
    src/Lion.cpp
    src/Tiger.cpp
    src/Bear.cpp
)

# Main executable
add_executable(zoo_keeper src/main.cpp ${SOURCE_FILES})
target_include_directories(zoo_keeper PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Test executable
add_executable(test_animals src/test.cpp ${SOURCE_FILES})
target_include_directories(test_animals PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Copy test input files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/test_input DESTINATION ${CMAKE_BINARY_DIR})
