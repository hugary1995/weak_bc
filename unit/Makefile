# CXX = g++
CXXFLAGS = -Wall -g -I ../include -I include
MPICC = g++

src = $(wildcard ../src/*.C) $(wildcard src/*.C)
src := $(filter-out ../src/main.C, $(src))
obj = $(src:.C=.o)

run_tests: $(obj)
	$(MPICC) -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
	rm -f ../src/*.o
	rm -f run_tests
