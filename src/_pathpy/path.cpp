#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

class Path{

  // Attributes of the Path class

  std::vector<int> relations;
  std::string name;


public:

  int uid;
  py::dict attributes;
  // Constructor declarations
  Path(std::vector<int> _rel, std::optional<int> _uid,
       const std::string &_name,const py::kwargs &kwargs);

  // Destructor declaration
  //~Path();

  // Methods of the Path class
  void set_name(const std::string &_name);
  const std::string &get_name();
  int get_uid();
  void test();
  py::tuple get_relations();
  auto __getitem__(const std::string& key);
  int __getitem__(int key);
  std::string __repr__();
};


Path::Path(std::vector<int> _rel, std::optional<int> _uid,
           const std::string &_name,const py::kwargs &kwargs)
{
  name = _name;
  if (!_uid.has_value()) {
    uid = -1;
  } else {
    uid = _uid.value();
  }
  relations = _rel;

  attributes = kwargs;

  if (kwargs){
    for (auto item : kwargs)
      std::cout << "key=" << std::string(py::str(item.first)) << ", "
                << "value=" << std::string(py::str(item.second)) << std::endl;

  }

  if(attributes.contains("color")){
    std::cout << "color = " << std::string(py::str(attributes["color"])) << std::endl;
  }
};

void Path::set_name(const std::string &_name)
{
  name = _name;
};

const std::string &Path::get_name()
{
  return name;
};

int Path::get_uid()
{
  return uid;
};

py::tuple Path::get_relations()
{
  return py::cast(relations);
};

auto Path::__getitem__(const std::string& key)
{
  return attributes[py::str(key)];
};

int Path::__getitem__(int key)
{
  return key;
};

std::string Path::__repr__()
{
  return "<pathpy.Path uid " + std::to_string(uid) + ">";
};

void Path::test()
{
  std::cout << "uid: " << uid << std::endl;

  if (relations.size() == 0){
    std::cout << "()" << std::endl;
  } else{
    std::cout << "(";
    for (size_t i = 0; i < relations.size()-1; i++)
      std::cout << relations[i] << ",";
    std::cout << relations.back() << ")" << std::endl;
  }
};


const char *doc_path = R"pbdoc(
        This is a class docstring for the Path class
    )pbdoc";


const char *doc_test = R"pbdoc(
        Function for testing code

        This is an arbitrary function to test c++ code.
    )pbdoc";

const char *doc_name = R"pbdoc(
        Name of the path
    )pbdoc";


void init_path(py::module &m) {
  py::class_<Path>(m, "Path",doc_path)
        .def(py::init<std::vector<int>,std::optional<int>,
             const std::string &,const py::kwargs &>(),
             py::arg("rel"), py::arg("uid") = py::none(),
             py::arg("name")="unknown")
        .def_property("name", &Path::get_name, &Path::set_name, doc_name)
        .def_property_readonly("uid", &Path::get_uid)
        .def_property_readonly("relations", &Path::get_relations)
        .def("__getitem__", py::overload_cast<int>(&Path::__getitem__),"Get int")
        .def("__getitem__", py::overload_cast<const std::string &>(&Path::__getitem__),"Get str")
        .def("__repr__", &Path::__repr__)
        .def("test", &Path::test, doc_test);
}
