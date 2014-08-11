#include <demo.h>

char const* greet()
{
   return xgreet();
}

bool parseCode(const char* code);

#include <boost/python.hpp>

BOOST_PYTHON_MODULE(hello)
{
    using namespace boost::python;
    def("greet", greet);
    def("parse_string", parseCode);
}