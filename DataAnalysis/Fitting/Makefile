hubble: hubble.cpp
	g++ -O3 -std=c++11 hubble.cpp -o hubble

supernova: supernova.cpp
	g++ -O3 -std=c++11 supernova.cpp -o supernova

quake: quake.cpp least_squares.hpp
	g++ -O3 -std=c++11 quake.cpp -o quake


all: hubble supernova quake

clean:
	rm -f *.o *~ hubble supernova quake
