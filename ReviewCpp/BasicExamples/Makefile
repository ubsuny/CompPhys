# From https://stackoverflow.com/questions/9787160/makefile-that-compiles-all-cpp-files-in-a-directory-into-separate-executable
CXX = g++
CXXFLAGS = -std=c++11

all: $(patsubst %.cc, %.out, $(wildcard *.cc))

%.out: %.cc Makefile
	$(CXX) $(CXXFLAGS) $< -o $(@:.out=)

clean: $(patsubst %.cc, %.clean, $(wildcard *.cc))

%.clean:
	rm -f $(@:.clean=)

