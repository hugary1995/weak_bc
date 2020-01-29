BUILD_DIR = build

CXXFLAGS = -Wall -g -I $(BUILD_DIR)/include -I eigen -I fparser
CXX = g++

src := $(wildcard src/**/*.C)
dep := $(wildcard include/**/*.h)
src_fparser := $(wildcard fparser/*.C)
obj_fparser := $(src_fparser:.C=.o)
src_build := $(wildcard $(BUILD_DIR)/src/*.C)
obj_build := $(src_build:.C=.o)

.PHONY: default prebuild build postbuild clean

default:
	make prebuild
	make build
	make postbuild

prebuild:
	rm -rf $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/src
	mkdir -p $(BUILD_DIR)/include
	cp $(src) $(BUILD_DIR)/src/.
	cp $(dep) $(BUILD_DIR)/include/.

build: $(obj_build) $(obj_fparser)
	$(CXX) -o run $(CXXFLAGS) $^

postbuild:
	rm -f $(BUILD_DIR)/src/*.C
	rm -f $(BUILD_DIR)/include/*.h

clean:
	rm -f src/**/*.o
	rm -f fparser/**/*.o
	rm -f run
