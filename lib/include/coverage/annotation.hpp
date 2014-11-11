#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

#include <string>
#include <vector>

namespace coverage {

struct Position {
  int line;
  int column;
};

struct Range {
  Position start;
  Position end;
};

struct Annotation {
  std::string name;
  Range visual;
  Range marker;
};

typedef std::vector<Annotation> Annotations;
}

#endif
