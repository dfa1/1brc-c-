CXX      := -c++
CXXFLAGS := -std=c++20 -pedantic-errors -W -Wall -Wextra -Werror -O3

all: main generator

main: main.cpp
	${CXX} ${CXXFLAGS} $< -o $@

generator: generator.cpp
	${CXX} ${CXXFLAGS} $< -o $@

measurements.txt: generator
	./generator

run: all measurements.txt
	./main

debug: CXXFLAGS += -g -pg
debug: all

clean:
	@rm -f main generator measurements.txt gmon.out

.PHONY: clean run
