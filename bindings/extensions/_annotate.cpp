
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <coverage/annotate.hpp>
#include <algorithm>

using namespace boost::python;
using namespace coverage;

Annotations annotate_with_parameter(const std::string code, list& l) {
  return annotate(code, Parameters(stl_input_iterator<std::string>(l),
                                   stl_input_iterator<std::string>()));
}

Annotations annotate_without_parameter(const std::string code) {
  return annotate(code);
}

template <class T>
struct VectorToListConverter {
  static PyObject* convert(const std::vector<T>& vec) {
    boost::python::list* l = new boost::python::list();

    for (auto& value : vec) {
      l->append(value);
    }

    return l->ptr();
  }
};

BOOST_PYTHON_MODULE(_annotate) {
  class_<Position>("Position")
      .def_readonly("line", &Position::line)
      .def_readonly("column", &Position::column)
      .def(self_ns::self == self_ns::self)
      .def(self_ns::str(self_ns::self));

  class_<Range>("Range")
      .def_readonly("start", &Range::start)
      .def_readonly("end", &Range::end)
      .def(self_ns::self == self_ns::self)
      .def(self_ns::str(self_ns::self));

  class_<Annotation>("Annotation")
      .def_readonly("name", &Annotation::name)
      .def_readonly("visual", &Annotation::visual)
      .def_readonly("marker", &Annotation::marker)
      .def(self_ns::self == self_ns::self)
      .def(self_ns::str(self_ns::self));

  to_python_converter<std::vector<Annotation>,
                      VectorToListConverter<Annotation> >();

  def("annotate", annotate_with_parameter);
  def("annotate", annotate_without_parameter);
}
