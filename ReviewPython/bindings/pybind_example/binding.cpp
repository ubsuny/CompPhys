#include <pybind11/pybind11.h>
#include <pybind11/stl.h>  // enables automatic std::vector <-> python list conversion
#include <pybind11/stl_bind.h> // For py::bind_vector
#include "example.h"

namespace py = pybind11;

PYBIND11_MAKE_OPAQUE(std::vector<long>);

PYBIND11_MODULE(example_pybind11, m) {
  m.doc() = "Simple pybind11 example (mirrors the SWIG example)";

  m.def("sum_int", &sum_int, "Sum a vector of ints",
        py::arg("vec"));

  m.def("sum_int_numpy", &sum_int_numpy, "Sum a numpy array of ints");

  m.def("sum_int_int", &sum_int_int, "Sum a vector of ints",
        py::arg("vec"));

  py::bind_vector<std::vector<long>>(m, "VectorLong"); // Make vector<int> available in python, as VectorInt

  py::bind_vector<std::vector<int>>(m, "VectorInt"); // Make vector<int> available in python, as VectorInt
}
