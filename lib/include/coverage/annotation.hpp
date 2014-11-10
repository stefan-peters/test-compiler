#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

#include <string>
#include <vector>

namespace coverage {

struct Annotation {
  Annotation(const std::string& name_ = "") : name(name_) {}
  std::string name;
};

typedef std::vector<Annotation> Annotations;
}

#endif
