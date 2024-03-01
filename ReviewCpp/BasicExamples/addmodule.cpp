/*
The keyword [ extern “C” ] is used to declare functions in C++ to be compiled in C. The compiler will use C libraries and won't screw up the function names. Also python is written in C and so you have to make sure that your C++ library is C callable.
*/
extern "C" int Add(int x, int y)
    {
        return x + y;
    }