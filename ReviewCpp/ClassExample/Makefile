make_a_point: Point.cc Point.h make_a_point.cc
	g++ -o make_a_point Point.cc make_a_point.cc -I.

read_points_example: Point.cc Point.h read_points_example.cc
	g++ -o read_points_example Point.cc read_points_example.cc -I.

all: make_a_point read_points_example

clean:
	rm -f *.o *~ make_a_point read_points_example
