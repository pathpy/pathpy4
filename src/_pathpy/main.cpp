#include <pybind11/pybind11.h>
#include <iostream>
#include <vector>
#include <pybind11/stl.h>


namespace py = pybind11;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}

py::tuple generic(const py::args &args, const py::kwargs &kwargs) {
  std::cout << "Test generic function with args" << std::endl;

  //args.cast<int>()
  py::tuple tup = py::make_tuple(42, py::none(), "spam");
  //for (auto & elem : args)      //
  //std::cout << args[0] << std::endl;

  std::vector<int> test_vec{1, 2, 3, 4, 5};
  py::tuple test_list3 = py::cast(test_vec);

  for (auto item : args)
    std::cout << std::string(py::str(item)) << std::endl;

  std::cout << sizeof(tup) << std::endl;
    // /// .. do something with args
  if (kwargs){
    for (auto item : kwargs)
      std::cout << "key=" << std::string(py::str(item.first)) << ", "
                << "value=" << std::string(py::str(item.second)) << std::endl;

  }
    //     /// .. do something with kwargs
  return test_list3;
}

void init_path(py::module &);

PYBIND11_MODULE(_pathpy, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: scikit_build_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("generic", &generic);

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    init_path(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
