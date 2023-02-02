cmake_minimum_required(VERSION 3.14)
project(fzd_gui)

# Set the output directory for the binary
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/src)
message("ASOA-Project root: ${PROJECT_SOURCE_DIR}")
message("Runtime file will be created in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

set(CMAKE_CXX_STANDARD 14)

# Include all directories from project root for the compiler
include_directories(${PROJECT_SOURCE_DIR})

# Include libraries
find_package(asoa_core 0.3 REQUIRED)


# Service executables
file(GLOB SERVICE_SRC
        "${PROJECT_SOURCE_DIR}/include/asoa_service/*.cpp"
        "${PROJECT_SOURCE_DIR}/include/asoa_service/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/asoa_service/interface/guarantees/*.hpp"
        "${PROJECT_SOURCE_DIR}/include/asoa_service/interface/requirements/*.hpp"
        )

# Create the executable
add_executable(${PROJECT_NAME} src/main.cpp ${SERVICE_SRC})
target_link_libraries(${PROJECT_NAME} asoa_core)

target_compile_definitions(${PROJECT_NAME}
        PRIVATE -Dfzd_gui_ROOT_DIR="${PROJECT_SOURCE_DIR}")


