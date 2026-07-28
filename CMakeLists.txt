cmake_minimum_required(VERSION 3.20)

project(ZeroCopyParser LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(
    -Wall
    -Wextra
    -Wpedantic
    -O3
    -march=native
)

include_directories(include)

add_executable(zero_copy_parser
    src/main.cpp
    src/udp_receiver.cpp
    src/ring_buffer.cpp
)

add_executable(sender
    src/sender.cpp
)

target_link_libraries(zero_copy_parser pthread)