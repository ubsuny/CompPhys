#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <vector>
#include <pybind11/numpy.h>
#include <cstdint>

namespace py = pybind11;

long sum_int(std::vector<long> const & vec);

int64_t sum_int_numpy(py::array_t<int64_t, py::array::c_style | py::array::forcecast> arr);

int sum_int_int(std::vector<int> const & vec);

#endif // EXAMPLE_H
