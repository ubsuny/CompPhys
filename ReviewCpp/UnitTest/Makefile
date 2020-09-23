all: a.out

a.out:
	g++ -Wno-psabi --std=c++11 hello.cpp

test: a.out
	./a.out

clean:
	rm a.out
