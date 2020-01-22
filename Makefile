# CXX = g++
CXXFLAGS = -Wall -g -I include
MPICC = mpicc

src = $(wildcard src/*.C)
obj = $(src:.C=.o)

run: $(obj)
	$(MPICC) -o $@ $^

.PHONY: clean

clean:
	rm -f src/*.o
	rm -f run
