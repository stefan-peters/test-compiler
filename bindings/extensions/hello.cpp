
#include <boost/python.hpp>

char const *greet() { return "hello, world"; }

bool parseCodeX(const char *code) { return true; }

typedef int ID;

struct Entity {
  ID id;
  std::string name;

  std::string getName() const { return name; }
  void setName(const std::string &name) { this->name = name; }
};

BOOST_PYTHON_MODULE(hello) {
  using namespace boost::python;
  def("greet", greet);
  def("parse_string", parseCodeX);

  class_<Entity>("Entity")
      .add_property("name", &Entity::getName, &Entity::setName);
}

// struct Relation {
// 	ID parent;
// 	std::list<ID> children;
// };

// struct Scope {
// 	ID id;
// 	std::string name;
// 	Relation rel;
// };

// typedef std::map<ID, Scope> Data;

// visiblity
// linkage
// translation unit

// local
// global

// ID!
// defined
// declared

// variables
// constants
// functions
// namespace
// methods
// enums
// types?
// arrays?