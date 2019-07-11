# Example of vectorization in C++ and python

Here we provide examples of using vectorization and loop unrolling in C++ and python. The C++ code should be compiled with g++ optimization options -O0, -O1, -O2:

```
g++ -std=c++11 vectorization.cpp -o vectorization -O0
```

or

```
g++ -std=c++11 vectorization.cpp -o vectorization -O1
```

or

```
g++ -std=c++11 vectorization.cpp -o vectorization -O2
```



The performances achieved are:

```
All times in microseconds
|                            |C++ -O0| C++ -O1| C++ -O2 | python | numpy |
|vector, unknown size        | 825   | 585    | 150     | 31862  | 460   |
|vector, known size          | 736   | 564    | 93      |        |       |
|static array                | 576   | 564    | 525     |        |       |
|static array, manual unroll | 132   | 97     | 93      |        |       |
```

Note: These used:
   - 2.9 GHz Intel Core i7
   - macOS Mojave 10.14.4
   - 16 GB 2133 MHz LPDDR3 RAM
   - Apple LLVM version 10.0.1 (clang-1001.0.46.3)
   - Python3 3.6.8
   - numpy 1.14.5
