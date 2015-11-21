# OpenBenchmark
OpenBenchmark is a small framework for benchmark testing. It's main focus is on simplicity for the user. 

### How to run
To use openbenchmark you just need to include the openbenchmark.hpp header file. Additionally you need to create an OpenBenchmark object to run them. 

``` cpp
#include "openbenchmark.hpp"

int main() {

	OpenBenchmark ob;
	ob.run_benchmarks();

	return 0;
}
```

### Usage examples:
Bechmark of a single statement:
``` cpp
BENCHMARK("A benchmark test in its simplest form", 2) {
	MEASURE( std::cout << "hello world" << std::endl );
}
```

Benchmark of multiple statements using C++11 lambda features:
``` cpp
BENCHMARK("Benchmark test to measure multiple statements", 4) {

	auto f = []() {
		std::cout << "Statement 1" << std::endl;
		std::cout << "Statement 2" << std::endl;
		std::cout << "Statement 3" << std::endl;
	};

	MEASURE( f() );
}
```

### Scalability
I you want to define multiple benchmarks, you can split them across several .cpp files. Its sufficient to include the openbenchmark.hpp header files in all .cpp files.

### Reporting
At the moment there is only one reporter available, the ConsoleReporter. 
