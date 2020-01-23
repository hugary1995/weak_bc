BUILD_DIR = build

CXXFLAGS = -Wall -g -I include -I eigen -I fparser
CXX = g++

src := $(wildcard src/**/*.C) $(wildcard fparser/*.C)
obj := $(src:.C=.o)

build: prepare
	echo "done"

prepare:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/src
	mkdir -p $(BUILD_DIR)/include
	cp $(src) $(BUILD_DIR)/.

run: $(obj)
	$(CXX) -o $@ $^

clean:
	rm -f src/**/*.o
	rm -f fparser/**/*.o
	rm -f run
