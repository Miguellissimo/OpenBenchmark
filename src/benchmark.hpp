#ifndef SRC_BENCHMARK_HPP_
#define SRC_BENCHMARK_HPP_

#include <vector>
#include <functional>
#include <iostream>
#include <chrono>
#include <ostream>

class Benchmark {
public:
	typedef std::chrono::microseconds microseconds;

	Benchmark(std::function<void(int)> f, std::string descr) : description(descr), func(f), cycles(10) { }

	void operator()() {
		//for (auto i = 0; i != cycles; ++i) {
		func(cycles);
		//}
	}

	std::ostream result();

private:
	std::vector<microseconds> ms;
	std::string description;
	std::function<void(int)> func;
	int cycles;

	double mean_microseconds() {
		double sum = 0.0;
		for (auto iter = ms.cbegin(); iter != ms.cend(); ++iter) {
			sum += iter->count();
		}

		return sum / ms.size();
	}
};

class Benchmarks {
private:
	Benchmarks() {};
	std::vector<std::function<void(int)>> x;

public:
	static Benchmarks& get_instance() {
		static Benchmarks instance;
		return instance;
	}

	static int register_benchmark(std::function<void(int)> f) {
		Benchmarks &inst = Benchmarks::get_instance();
		inst.add(f);
		return 1;
	}

	void add(std::function<void(int)> f) {
		x.push_back(f);
	}

	int number_of_benchmarks() {
		return x.size();
	}

	void run() {
		for (auto func : x) {
			if (func != nullptr) {
				func(10);
			}
		}
	}
};

#define INTERNAL_NAMESPACE_NAME2( name, line ) name##line
#define INTERNAL_NAMESPACE_NAME( name, line ) INTERNAL_BENCHMARK_NAME2( name, line )

#define INTERNAL_BENCHMARK_NAME2( name, line ) name##line
#define INTERNAL_BENCHMARK_NAME( name, line ) INTERNAL_BENCHMARK_NAME2( name, line )
#define MAKE_BENCHMARK_NAME( name ) INTERNAL_BENCHMARK_NAME( name, __LINE__ )

#define RUN_BENCHMARKS() \
Benchmarks::get_instance(); \
std::cout << "number of registered benchmarks: " << Benchmarks::get_instance().number_of_benchmarks() << std::endl; \
Benchmarks::get_instance().run();

#define INTERNAL_BENCHMARK( function_name, description ) \
static void function_name(int __openbenchmark__internal__cycles); \
namespace{ \
	auto INTERNAL_NAMESPACE_NAME(bm, __LINE__) = Benchmarks::register_benchmark(&function_name); \
}; \
static void function_name(int __openbenchmark__internal__cycles)

#define BENCHMARK( description ) INTERNAL_BENCHMARK(MAKE_BENCHMARK_NAME(benchmark_function__), description)

#define MEASURE(x) \
int i = 0; \
while (i < __openbenchmark__internal__cycles) { \
	auto start = std::chrono::high_resolution_clock::now(); \
	x; \
	auto diff = std::chrono::high_resolution_clock::now() - start; \
	std::cout << std::chrono::duration_cast<std::chrono::microseconds>(diff).count() << "ms" << std::endl; \
	i++;\
}

#endif /* SRC_BENCHMARK_HPP_ */
