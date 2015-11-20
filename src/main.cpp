#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <memory>
#include "benchmark.hpp"

BENCHMARK("A benchmark test in its simplest form") {
	MEASURE( std::cout << "second benchmark" << std::endl )
}

BENCHMARK("Benchmark test to measure multiple statements") {

	auto f = []() {
		std::cout << "Statement 1" << std::endl;
		std::cout << "Statement 2" << std::endl;
		std::cout << "Statement 3" << std::endl;
	};

	MEASURE( f() )
}

int main() {
	RUN_BENCHMARKS();
	return 0;
}