
#include <boost/python.hpp>
#include <coverage/annotate.hpp>

BOOST_PYTHON_MODULE(_annotate) {
  using namespace boost::python;
  def("annotate", coverage::annotate);
}
