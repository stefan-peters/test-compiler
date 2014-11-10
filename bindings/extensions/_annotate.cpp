
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

    
    for (const T& value : vec) {
      l->append(value);
    }

    return l->ptr();
  }
};

BOOST_PYTHON_MODULE(_annotate) {
  class_<Annotation>("Annotation").def_readonly("name", &Annotation::name);

  to_python_converter<std::vector<Annotation>,
                      VectorToListConverter<Annotation> >();

  def("annotate", annotate_with_parameter);
  def("annotate", annotate_without_parameter);
}
