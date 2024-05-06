CXX      := g++
CXXFLAGS := -std=c++20 -pedantic-errors -W -Wall -Wextra -Werror -O3 -march=native
SHELL    := bash

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

format:
	clang-format --style=Google -i *.cpp *.h

TIMES ?= 5

benchmark: all measurements.txt
	for i in {1..${TIMES}}; do time ./main; done

clean:
	@rm -f main generator measurements.txt gmon.out

.PHONY: clean run format benchmark
