#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <memory>
#include "benchmark.hpp"

BENCHMARK("A benchmark test in its simplest form", 2) {
	MEASURE( std::cout << "second benchmark" << std::endl );
}

BENCHMARK("Benchmark test to measure multiple statements", 4) {

	auto f = []() {
		std::cout << "Statement 1" << std::endl;
		std::cout << "Statement 2" << std::endl;
		std::cout << "Statement 3" << std::endl;
	};

	MEASURE( f() );
}

int main() {

	OpenBenchmark ob;
	ob.run_benchmarks();

	return 0;
}
