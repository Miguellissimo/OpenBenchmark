#ifndef SRC_BENCHMARK_HPP_
#define SRC_BENCHMARK_HPP_

#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <ostream>
#include <memory>

typedef std::chrono::high_resolution_clock::duration microseconds;

struct BenchmarkResult {
	BenchmarkResult() {}

	std::string description;
	int cycles;
	double duration_mean;
	double duration_max;
	double duration_min;

private:
	friend std::ostream& operator<<(std::ostream&, const BenchmarkResult&);
};

inline std::ostream& operator<<(std::ostream &os, const BenchmarkResult &br) {
	return os << "----------------------------------------" << std::endl
			  << br.description << std::endl
			  << "----------------------------------------" << std::endl
			  << "Min runtime:  " << br.duration_min << " ms" << std::endl
			  << "Mean runtime: " << br.duration_mean << " ms" << std::endl
			  << "Max runtime:  " << br.duration_max << " ms" << std::endl;
}

class Benchmark {
public:
	Benchmark(std::function<void(int, std::shared_ptr<std::vector<microseconds>>)> f, std::string descr, int i) : description(descr), func(f), cycles(i) {
		ms = std::make_shared<std::vector<microseconds>>();
	}

	BenchmarkResult operator()() {
		func(cycles, ms);
		return result();
	}

	BenchmarkResult result() {
		BenchmarkResult res;
		res.description = description;
		res.duration_mean = mean_microseconds();
		auto minmax = std::minmax_element(ms->cbegin(), ms->cend());
		res.duration_min = std::chrono::duration_cast<std::chrono::microseconds>(*(minmax.first)).count();
		res.duration_max = std::chrono::duration_cast<std::chrono::microseconds>(*(minmax.second)).count();
		res.cycles = cycles;

		return res;
	}

private:
	std::shared_ptr<std::vector<microseconds>> ms;
	std::string description;
	std::function<void(int, std::shared_ptr<std::vector<microseconds>>)> func;
	int cycles;

	double mean_microseconds() {
		double sum = 0.0;
		for (auto iter = ms->cbegin(); iter != ms->cend(); ++iter) {
			auto dur = std::chrono::duration_cast<std::chrono::microseconds>(*iter);
			sum += dur.count();
		}

		return sum / ms->size();
	}
};

class Benchmarks {
private:
	Benchmarks() {};
	std::vector<Benchmark> x;

public:
	static Benchmarks& get_instance() {
		static Benchmarks instance;
		return instance;
	}

	static int register_benchmark(Benchmark b) {
		Benchmarks &inst = Benchmarks::get_instance();
		inst.add(b);
		return 1;
	}

	void add(Benchmark b) {
		x.push_back(b);
	}

	int number_of_benchmarks() {
		return x.size();
	}

	void run() {
		for (auto benchmark : x) {
			auto res = benchmark();
			std::cout << res << std::endl;
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

#define INTERNAL_BENCHMARK( function_name, description, cycles ) \
static void function_name(int __openbenchmark__internal__cycles, std::shared_ptr<std::vector<microseconds>> __openbenchmark__internal__ms); \
namespace{ \
	auto INTERNAL_NAMESPACE_NAME(bm, __LINE__) = Benchmarks::register_benchmark(Benchmark(&function_name, description, cycles)); \
}; \
static void function_name(int __openbenchmark__internal__cycles, std::shared_ptr<std::vector<microseconds>> __openbenchmark__internal__ms)

#define BENCHMARK( description, cycles ) INTERNAL_BENCHMARK(MAKE_BENCHMARK_NAME(benchmark_function__), description, cycles)

#define MEASURE(x) \
int i = 0; \
while (i < __openbenchmark__internal__cycles) { \
	auto start = std::chrono::high_resolution_clock::now(); \
	x; \
	auto diff = std::chrono::high_resolution_clock::now() - start; \
	__openbenchmark__internal__ms->push_back(diff);\
	++i;\
}

#endif /* SRC_BENCHMARK_HPP_ */
