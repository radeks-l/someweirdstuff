#include <benchmark/benchmark.h>

#include "BigInt.hpp"



static void BM_SomeFunction(benchmark::State& state) {
  // Perform setup here
  BigInt s(0);
  for (auto _ : state) {
    // This code gets timed
    s = s + BigInt(1);
  }
}

// Register the function as a benchmark
BENCHMARK(BM_SomeFunction);

BENCHMARK_MAIN();