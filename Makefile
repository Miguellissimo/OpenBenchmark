# specify the used compiler
CXX = clang++

# specified compiler flags
CFLAGS = -std=c++1y -Wall -stdlib=libc++
CPP_FILES := $(wildcard src/*.cpp)
SRC_DIR = -I./src

all: debug

release:
	$(CXX) $(CFLAGS) $(CPP_FILES) -o main

debug:
	$(CXX) $(CFLAGS) -g -O0 $(CPP_FILES) -o main

clean:
	rm -f *.o main

run:
	./main