cmake_minimum_required(VERSION 3.10)
project(RequiemDB VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

# Define sources
set(SOURCES
    src/main.cpp
    src/requiemstore.cpp
    src/server.cpp
)

# Create the executable
add_executable(RequiemDB ${SOURCES})

# Tell the compiler where to look for headers
target_include_directories(RequiemDB PRIVATE include)

if (WIN32)
    target_link_libraries(RequiemDB ws2_32)
endif()