
#include "module_A.h"
#include "benchmark.hpp"

BENCHMARK("benchmark simple operation from module A", 5) {
	MEASURE( do_something_simple() );
}

BENCHMARK("benchmark moderate operation from module A", 5) {
	MEASURE( do_something_moderate() );
}

BENCHMARK("benchmark complex operation from module A", 5) {
	MEASURE( do_something_complex() );
}
