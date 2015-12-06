# OpenBenchmark
OpenBenchmark is a small C++ framework for benchmark tests which was started on a Hackathon. The idea came up from Chandler Carruth's talk at CppCon 2015 on the topic [Tuning C++: Benchmarks, and CPUs, and Compilers](https://www.youtube.com/watch?v=nXaxk27zwlk). It's main focus is on the simplicity for the user. For this, the style from Phil Nash's awesome testing framework [Catch](https://github.com/philsquared/Catch) was copied to provide a similiar structure.

### How to install and execute
OpenBenchmark is a header file only library which needs just to be included in the source files where the benchmark tests should be defined. To run them an OpenBenchmark instance has to be created. The following listing shows an example main function.

``` cpp
#include "openbenchmark.hpp"

int main() {

	OpenBenchmark ob;
	ob.run_benchmarks();

	return 0;
}
```

### Usage examples:
The simplest form of a benchmark test has the following form:
``` cpp
BENCHMARK("A benchmark test in its simplest form", 2) {
	MEASURE( std::cout << "hello world" << std::endl );
}
```
The macro __BENCHMARK__ is the starting point which takes two parameters. The first one is a string which describes what the benchmark should measure. The second one defines the number of runs. 
The macro __MEASURE__ executes the given statement *n*-times.

If you want to measure multiple statements at once you can use C\+\+11 lambdas to group them together and pass that function to the __MEASURE__ macro.

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

The space in the __BENCHMARK__ body before the measuring starts can be used to set up the different parameters which need to be passed to the function. This part gets only run once.  

``` cpp
BENCHMARK(" ... ", 10) {
    // this space can be used to gather all pieces, information 
    // and objects which need to be passed to the function that
    // should be measured. 
    
	MEASURE( ... );
}
```

### Scalability
I you want to define multiple benchmarks, you can split them across several .cpp files. Its sufficient to include the openbenchmark.hpp header in the corresponding .cpp files.

### Reporting
At the moment there is only one reporter available, the ConsoleReporter. 