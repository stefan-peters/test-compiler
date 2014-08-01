#define BOOST_TEST_MODULE demo
#include <boost/test/unit_test.hpp>


int sqr(int x) {
  return x * x;
}

BOOST_AUTO_TEST_CASE(FailTest)
{
    BOOST_CHECK_EQUAL(5, sqr(2));
}

BOOST_AUTO_TEST_CASE(PassTest)
{
    BOOST_CHECK_EQUAL(4, sqr(2));
}
