read_points_example: Point.cc Point.h read_points_example.cc
	g++ -o read_points_example Point.cc read_points_example.cc -I.

read_points_example_strstream: Point.cc Point.h read_points_example.cc
	g++ -o read_points_example_strstream Point.cc read_points_example_strstream.cc -I.

all: read_points_example_strstream read_points_example

clean:
	rm -f *.o *~ read_points_example_strstream read_points_example
