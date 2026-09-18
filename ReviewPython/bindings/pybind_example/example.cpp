#include "example.h"

long sum_int(std::vector<long> const & vec)
{
  long sum = 0;
  for ( auto i : vec ) {
    sum += i;
  }
  return sum;
}

int64_t sum_int_numpy(py::array_t<int64_t, py::array::c_style | py::array::forcecast> arr) {
    py::buffer_info buf = arr.request();      // inspect the array without copying
    int64_t* ptr = static_cast<int64_t*>(buf.ptr);    // raw pointer straight into numpy's memory
    int64_t sum = 0;
    for (ssize_t i = 0; i < buf.size; i++) {
        sum += ptr[i];
    }
    return sum;
}
