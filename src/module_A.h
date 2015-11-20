
#include <vector>

void do_something_simple() {
	std::vector<int>(10);
}

void do_something_moderate() {
	for (auto i = 0; i != 100; ++i) {
		std::vector<int>(10);
	}
}

void do_something_complex() {

}
