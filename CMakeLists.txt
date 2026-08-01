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
    src/parser.cpp
    src/market_handler.cpp
    src/decoder.cpp
    src/order_book.cpp
)

add_executable(sender
    src/sender.cpp
)

target_link_libraries(zero_copy_parser pthread)

# Unit Tests (catch)
enable_testing()

add_executable(unit_tests
    tests/test_main.cpp
    tests/test_ring_buffer.cpp
    tests/test_packet_pool.cpp
    tests/test_order_book.cpp

    src/order_book.cpp
    src/decoder.cpp
    src/market_handler.cpp
)

target_include_directories(unit_tests PRIVATE
    include
    tests
)

target_link_libraries(unit_tests pthread)

add_test(NAME UnitTests COMMAND unit_tests)

# Benchmarks (Google Benchmark)
add_executable(benchmarks
    benchmarks/bench_ring_buffer.cpp
    benchmarks/bench_packet_pool.cpp
    benchmarks/bench_order_book.cpp
    benchmarks/bench_pipeline.cpp

    src/order_book.cpp
)

target_include_directories(benchmarks PRIVATE
    include
    /usr/include
)

target_link_libraries(benchmarks
    benchmark
    pthread
)