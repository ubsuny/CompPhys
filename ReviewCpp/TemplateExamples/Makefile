test_storage: Point.cc Point.h Storage.h test_storage.cc
	g++ -std=c++11 -o test_storage Point.cc test_storage.cc -I.

vector3: Vector3.h make_a_vector.cc
	g++ -std=c++11 -o make_a_vector.exe make_a_vector.cc -I.

all: test_storage vector3

clean:
	rm -f *.o *~ test_storage make_a_vector.exe
