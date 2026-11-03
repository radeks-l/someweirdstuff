#include <benchmark/benchmark.h>

#include "BigInt.hpp"

static void BM_operator_add(benchmark::State& state) {
  // Perform setup here
  BigInt s(0);
  for (auto _ : state) {
    // This code gets timed
    s = s + BigInt(1000);
  }
}

static void BM_operator_mul(benchmark::State& state) {
  // Perform setup here
  BigInt s(0);
  for (auto _ : state) {
    // This code gets timed
    s = s * BigInt(13);
  }
}

static void BM_operator_uint64(benchmark::State& state) {
  // Perform setup here
  uint64_t s = 0;
  for (auto _ : state) {
    // This code gets timed
    s = s + static_cast<uint64_t>(BigInt(10000));
  }
}

// Register the function as a benchmark
BENCHMARK(BM_operator_mul);

BENCHMARK_MAIN();