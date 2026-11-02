cmake_minimum_required(VERSION 3.19)

project(BigInt)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        1da23a3e8119ec5cce4f9388e91b065e20bf06f5 # v2.4.12
)

set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG        eddb0241389718a23a42db6af5f0164b6e0139af # v1.9.4
)

FetchContent_MakeAvailable(doctest benchmark)

add_executable(ut_bigint test.cpp BigInt.cpp)
target_link_libraries(ut_bigint doctest)

add_executable(bigint_benchmark benchmark.cpp BigInt.cpp)
target_link_libraries(bigint_benchmark benchmark)
