cmake_minimum_required(VERSION 3.10)
project(api)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler flags for warnings and errors
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

# Add the thread library
find_package(Threads REQUIRED)

# Add the source file
set(SOURCES api.cpp)

# Create the executable
add_executable(api ${SOURCES})

# Link the executable with the thread library
target_link_libraries(api Threads::Threads rt)

