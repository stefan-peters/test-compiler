#ifndef ANNOTATION_HPP
#define ANNOTATION_HPP

#include <string>
#include <vector>

namespace coverage {

struct Annotation {
  std::string name;
};

typedef std::vector<Annotation> AnnotationList;
}

#endif
