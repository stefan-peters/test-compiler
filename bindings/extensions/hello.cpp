#include <demo.h>

char const* greet()
{
   return xgreet();
}

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(hello)
{
    using namespace boost::python;
    def("greet", greet);
}