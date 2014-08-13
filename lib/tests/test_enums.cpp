#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cmc/container.h>
#include <cmc/parser.h>

namespace cmc {
	void PrintTo(const Enum& e, ::std::ostream* os) {
 	 	*os << "Enum(" << e.name << ") {}";
	}
}

std::list<cmc::Enum> colorEnum() {

  std::list<cmc::Enum> l;
  cmc::Enum e;
  e.name = "Color";
  e.values.push_back(make_tuple(std::string("Red"), 0));
  e.values.push_back(make_tuple(std::string("Green"), 1));
  e.values.push_back(make_tuple(std::string("Blue"), 2));
  l.push_back(e);
  return l;
}

TEST(EnumTests, NormalEnum) {
  ASSERT_EQ(colorEnum(), cmc::parseCode("enum Color {Red, Green, Blue};"));
}

TEST(EnumTests, TypedefEnum) {
  ASSERT_EQ(colorEnum(),
            cmc::parseCode("typedef enum {Red, Green, Blue} Color;"));
}

TEST(EnumTests, ClassEnum) {
  ASSERT_EQ(colorEnum(),
            cmc::parseCode("enum class Color {Red, Green, Blue};"));
}

// otool -L --> ldd