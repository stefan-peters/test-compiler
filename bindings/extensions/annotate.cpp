
#include <boost/python.hpp>
#include <coverage/annotate.hpp>

BOOST_PYTHON_MODULE(annotate) {
  using namespace boost::python;
  def("annotate", coverage::annotate);
  //   def("parse_string", parseCodeX);
  //
  //   class_<Entity>("Entity")
  //       .add_property("name", &Entity::getName, &Entity::setName);
}
