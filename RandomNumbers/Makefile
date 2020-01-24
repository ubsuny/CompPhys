CXX=g++
CXXFLAGS = -std=c++11 -O3
all: run_ising

ising.o:
	$(CXX) $(CXXFLAGS) -c ising.cpp -o ising.o

run_ising: ising.o run_ising.cpp
	$(CXX) ising.o run_ising.cpp  $(CXXFLAGS) -o run_ising

clean:
	rm -rf *o run_ising
