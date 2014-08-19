#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include <cmc/container.h>
#include <cmc/parser.h>

namespace cmc {
void PrintTo(const Enum &e, ::std::ostream *os) {
  *os << "Enum(" << e.name << ") { ";
  for(auto value : e.values) {
  	*os << std::get<0>(value) << ":" << std::get<1>(value) << " ";
  }
  *os << "}";
}

}

std::list<cmc::Enum> colorEnum(const std::string& name = "Color") {

  std::list<cmc::Enum> l;
  cmc::Enum e(name);
  e.values.push_back(make_tuple(std::string("Red"), 0));
  e.values.push_back(make_tuple(std::string("Green"), 1));
  e.values.push_back(make_tuple(std::string("Blue"), 2));
  l.push_back(e);
  return l;
}

TEST(EnumTests, EmptyEnum) {

  std::list<cmc::Enum> l;
  cmc::Enum e("Empty");
  l.push_back(e);

  ASSERT_EQ(l, cmc::parseCode("enum Empty {};"));
}

TEST(EnumTests, AnonymousEnumWithoutAnyTypedef) {

  std::list<cmc::Enum> l;
  cmc::Enum e;
  e.values.push_back(make_tuple(std::string("X"), 0));
  l.push_back(e);

  ASSERT_EQ(l, cmc::parseCode("enum {X};"));
}

TEST(EnumTests, NormalEnum) {
  ASSERT_EQ(colorEnum(), cmc::parseCode("enum Color {Red, Green, Blue};"));
}

TEST(EnumTests, TypedefEnum) {
  ASSERT_EQ(colorEnum(),
            cmc::parseCode("typedef enum {Red, Green, Blue} Color;"));
}

TEST(EnumTests, ClassEnum) {
  std::vector<std::string> args;
  args.push_back("--std=c++11");
  ASSERT_EQ(colorEnum(),
            cmc::parseCode("enum class Color {Red, Green, Blue};", args));
}

TEST(EnumTests, RealNameVsTypedef) {
  ASSERT_EQ(colorEnum(), cmc::parseCode("enum Color {Red, Green, Blue}; typedef Color Colour;"));
}

TEST(EnumTests, ComplexNumbering) {
  ASSERT_EQ(colorEnum(), cmc::parseCode("enum Color {Red, Green, Blue = Green * 2};"));
}

TEST(EnumTests, SimpleReordering) {
  ASSERT_EQ(colorEnum(), cmc::parseCode("enum Color {Blue = 2, Red = 0, Green = 1};"));
}

TEST(EnumTests, EnumsInsideNamespaces) {
  ASSERT_EQ(colorEnum("NS::Color"), cmc::parseCode("namespace NS { enum Color {Red, Green, Blue}; }"));
}

TEST(EnumTests, EnumsWithQualifiedNamesInClasses) {
  ASSERT_EQ(colorEnum("CL::Color"), cmc::parseCode("class CL { public: enum Color {Red, Green, Blue}; };"));
  ASSERT_EQ(colorEnum("CL::Color"), cmc::parseCode("class CL { private: typedef enum {Red, Green, Blue} Color; };"));
  ASSERT_EQ(colorEnum("CL::Color"), cmc::parseCode("struct CL { enum Color {Red, Green, Blue}; };"));
  ASSERT_EQ(colorEnum("NS::CL::Color"), cmc::parseCode("namespace NS {struct CL { enum Color {Red, Green, Blue}; }; }"));
}

TEST(EnumTests, MultipleEnums) {

  auto l = colorEnum();
  cmc::Enum e("Priority");
  e.values.push_back(make_tuple(std::string("High"), 0));
  l.push_back(e);

  ASSERT_EQ(l, cmc::parseCode("enum Color {Red, Green, Blue}; enum Priority{High};"));
}

TEST(EnumTests, EnumInAnonymouseNamespace) {

  auto l = colorEnum();

  ASSERT_EQ(l, cmc::parseCode("namespace { enum Color {Red, Green, Blue}; }"));
}

TEST(EnumTests, AnonymousEnumInClass) {

  std::list<cmc::Enum> l;
  cmc::Enum e;
  e.values.push_back(make_tuple(std::string("X"), 0));
  l.push_back(e);

  ASSERT_EQ(l, cmc::parseCode("class CL { enum {X}; };"));
}

// otool -L --> ldd